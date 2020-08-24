/******************************************************************************/
/*                                                                            */
/* src/State/StateExec.c                                                      */
/*                                                                 2020/08/22 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibState.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* ローカル関数宣言                                                           */
/******************************************************************************/
/* 状態遷移実行(内部関数) */
static MLibRet_t Exec( MLibState_t      *pHandle,
                       MLibStateEvent_t event,
                       void             *pArg,
                       MLibStateNo_t    *pPrevState,
                       MLibStateNo_t    *pNextState,
                       MLibErr_t        *pErr        );
/* 状態遷移タスク実行 */
static MLibRet_t ExecTask( MLibState_t                 *pHandle,
                           const MLibStateTransition_t *pTransition,
                           void                        *pArg,
                           MLibStateNo_t               *pNextState,
                           MLibErr_t                   *pErr         );


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief           状態遷移実行
 * @details         状態遷移表に従って状態とイベントに対応する状態遷移タスクを
 *                  実行する。
 *
 * @param[in]       *pHandle    状態遷移ハンドル
 * @param[in]       event       イベント番号
 * @param[in]       *pArg       状態遷移タスク引数
 * @param[out]      *pPrevState 遷移前状態
 * @param[out]      *pNextState 遷移先状態
 * @param[out]      *pErr       エラー要因
 *                      - MLIB_ERR_NONE    エラー無し
 *                      - MLIB_ERR_PARAM   パラメータ不正
 *                      - MLIB_ERR_NOTRANS 状態遷移無し
 *                      - MLIB_ERR_TRANS   状態遷移不正
 *
 * @return          処理結果を返す。
 * @retval          MLIB_RET_SUCCESS 正常終了
 * @retval          MLIB_RET_FAILURE 異常終了
 *
 * @note            本関数はスピンロックを用いて排他する。
 */
/******************************************************************************/
MLibRet_t MLibStateExec( MLibState_t      *pHandle,
                         MLibStateEvent_t event,
                         void             *pArg,
                         MLibStateNo_t    *pPrevState,
                         MLibStateNo_t    *pNextState,
                         MLibErr_t        *pErr        )
{
    MLibRet_t ret;  /* 戻り値 */

    /* 初期化 */
    ret = MLIB_RET_FAILURE;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* 状態遷移ハンドルチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pHandle->lock ), NULL );

    /* 遷移前状態設定 */
    MLIB_SET_IFNOT_NULL( pPrevState, pHandle->state );

    /* 状態遷移実行(内部関数) */
    ret = Exec( pHandle, event, pArg, pPrevState, pNextState, pErr );

    /* 遷移先状態設定 */
    MLIB_SET_IFNOT_NULL( pNextState, pHandle->state );

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle->lock ), NULL );

    return ret;
}


/******************************************************************************/
/* ローカル関数定義                                                           */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief           状態遷移実行(内部関数)
 * @details         状態遷移表に従って状態とイベントに対応する状態遷移タスクを
 *                  実行する。
 *
 * @param[in]       *pHandle    状態遷移ハンドル
 * @param[in]       event       イベント番号
 * @param[in]       *pArg       状態遷移タスク引数
 * @param[out]      *pPrevState 遷移前状態
 * @param[out]      *pNextState 遷移先状態
 * @param[out]      *pErr       エラー要因
 *                      - MLIB_ERR_PARAM   パラメータ不正
 *                      - MLIB_ERR_NOTRANS 状態遷移無し
 *
 * @return          処理結果を返す。
 * @retval          MLIB_RET_SUCCESS 正常終了
 * @retval          MLIB_RET_FAILURE 異常終了
 */
/******************************************************************************/
static MLibRet_t Exec( MLibState_t      *pHandle,
                       MLibStateEvent_t event,
                       void             *pArg,
                       MLibStateNo_t    *pPrevState,
                       MLibStateNo_t    *pNextState,
                       MLibErr_t        *pErr        )
{
    uint32_t                    idx;      /* 状態遷移表インデックス */
    const MLibStateTransition_t *pEntry;  /* 状態遷移表エントリ     */

    /* 初期化 */
    idx    = 0;
    pEntry = NULL;

    /* 全状態遷移毎に繰り返し */
    for ( idx = 0; idx < pHandle->transitionNum; idx++ ) {
        /* 状態遷移表エントリ参照先設定 */
        pEntry = &( pHandle->pTable[ idx ] );

        /* 該当状態遷移判定 */
        if ( (   pEntry->state == pHandle->state             ) &&
             ( ( pEntry->event == event                 ) ||
               ( pEntry->event == MLIB_STATE_EVENT_NULL )    )    ) {
            /* 一致 */

            /* 状態遷移タスク実行 */
            return ExecTask( pHandle, pEntry, pArg, pNextState, pErr );
        }
    }

    /* エラー要因設定 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOTRANS );

    return MLIB_RET_FAILURE;
}


/******************************************************************************/
/**
 * @brief           状態遷移タスク実行
 * @details         状態遷移に登録されたタスクを起動する。遷移先状態が状態遷移
 *                  表通りか判定する。
 *
 * @param[in]       *pHandle     状態遷移ハンドル
 * @param[in]       *pTransition 状態遷移
 * @param[in]       *pArg        状態遷移タスク引数
 * @param[out]      *pNextState  遷移先状態
 * @param[out]      *pErr        エラー要因
 *                      - MLIB_ERR_PARAM パラメータ不正
 *                      - MLIB_ERR_TRANS 状態遷移不正
 *
 * @return          処理結果を返す。
 * @retval          MLIB_RET_SUCCESS 正常終了
 * @retval          MLIB_RET_FAILURE 異常終了
 */
/******************************************************************************/
static MLibRet_t ExecTask( MLibState_t                 *pHandle,
                           const MLibStateTransition_t *pTransition,
                           void                        *pArg,
                           MLibStateNo_t               *pNextState,
                           MLibErr_t                   *pErr         )
{
    uint32_t      idx;    /* 遷移先インデックス */
    MLibStateNo_t state;  /* 遷移先状態         */

    /* 初期化 */
    idx   = 0;
    state = MLIB_STATE_NULL;

    /* 状態遷移タスク有無判定 */
    if ( pTransition->task == NULL ) {
        /* タスク無し */

        /* 状態遷移先判定 */
        if ( pTransition->next[ 0 ] == MLIB_STATE_NULL ) {
            /* 不正 */

            /* エラー要因設定 */
            MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_TRANS );

            return MLIB_RET_FAILURE;
        }

        /* 遷移先状態設定 */
        pHandle->state = pTransition->next[ 0 ];

        return MLIB_RET_SUCCESS;

    }

    /* 状態遷移タスク起動 */
    state = ( pTransition->task )( pArg );

    /* 遷移先状態毎に繰り返し */
    for ( idx = 0; idx < MLIB_STATE_NEXT_NUM; idx++ ) {
        /* 遷移先状態判定 */
        if ( pTransition->next[ idx ] == state ) {
            /* 一致 */

            /* 遷移先状態設定 */
            pHandle->state = state;

            return MLIB_RET_SUCCESS;

        } else if ( pTransition -> next[ idx ] == 0 ) {
            /* 終端 */

            break;
        }
    }

    /* エラー要因設定 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_TRANS );

    return MLIB_RET_FAILURE;
}


/******************************************************************************/
