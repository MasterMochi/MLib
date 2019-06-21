/******************************************************************************/
/*                                                                            */
/* src/State/StateExec.c                                                      */
/*                                                                 2019/06/21 */
/* Copyright (C) 2019 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibState.h>


/******************************************************************************/
/* ローカル関数宣言                                                           */
/******************************************************************************/
static MLibRet_t ExecTask( MLibStateHandle_t           *pHandle,
                           const MLibStateTransition_t *pTransition,
                           void                        *pArg,
                           MLibState_t                 *pNextState,
                           uint32_t                    *pErrNo       );


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief           状態遷移実行
 * @details         状態遷移ハンドル(*pHandle)が管理する状態にイベント(event)を
 *                  入力し、状態遷移表に従った状態遷移タスクを実行する。
 *
 * @param[in/out]   *pHandle    状態遷移ハンドル
 * @param[in]       event       イベント番号
 * @param[in]       *pArg       状態遷移タスク引数
 * @param[out]      *pPrevState 遷移前状態
 * @param[out]      *pNextState 遷移先状態
 * @param[out]      *pErrNo     エラー番号
 *                      - MLIB_STATE_ERR_NONE     エラー無し
 *                      - MLIB_STATE_ERR_PARAM    パラメータエラー
 *                      - MLIB_STATE_ERR_NO_TRANS 状態遷移無し
 *
 * @return          処理結果を返す。
 * @retval          MLIB_SUCCESS 正常終了
 * @retval          MLIB_FAILURE 異常終了
 */
/******************************************************************************/
MLibRet_t MLibStateExec( MLibStateHandle_t *pHandle,
                         MLibStateEvent_t  event,
                         void              *pArg,
                         MLibState_t       *pPrevState,
                         MLibState_t       *pNextState,
                         uint32_t          *pErrNo      )
{
    uint32_t idx;   /* カウンタ */

    /* 初期化 */
    idx = 0;

    /* エラー番号初期化 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_NONE );

    /* 状態遷移ハンドルチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* 遷移前状態設定 */
    MLIB_SET_IFNOT_NULL( pPrevState, pHandle->state );

    /* 全状態遷移毎に繰り返し */
    for ( idx = 0; idx < pHandle->transitionNum; idx++ ) {
        /* 該当状態遷移判定 */
        if ( ( pHandle->state == pHandle->pTable[ idx ].state ) &&
             ( event          == pHandle->pTable[ idx ].event )    ) {
            /* 一致 */

            /* 状態遷移タスク実行 */
            return ExecTask( pHandle,
                             &( pHandle->pTable[ idx ] ),
                             pArg,
                             pNextState,
                             pErrNo                       );
        }
    }

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_NO_TRANS );

    return MLIB_FAILURE;
}


/******************************************************************************/
/* ローカル関数定義                                                           */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief           状態遷移タスク実行
 * @details         状態遷移(*pTransition)に登録されたタスクを起動する。遷移先
 *                  状態が状態遷移通りか判定する。
 *
 * @param[in/out]   *pHandle     状態遷移ハンドル
 * @param[in]       *pTransition 状態遷移
 * @param[in]       *pArg        状態遷移タスク引数
 * @param[out]      *pNextState  遷移先状態
 * @param[out]      *pErrNo      エラー番号
 *                      - MLIB_STATE_ERR_NONE  エラー無し
 *                      - MLIB_STATE_ERR_PARAM パラメータエラー
 *                      - MLIB_STATE_ERR_TRANS 不正状態遷移
 *
 * @return          処理結果を返す。
 * @retval          MLIB_SUCCESS 正常終了
 * @retval          MLIB_FAILURE 異常終了
 */
/******************************************************************************/
static MLibRet_t ExecTask( MLibStateHandle_t           *pHandle,
                           const MLibStateTransition_t *pTransition,
                           void                        *pArg,
                           MLibState_t                 *pNextState,
                           uint32_t                    *pErrNo       )
{
    uint32_t    idx;    /* カウンタ   */
    MLibState_t state;  /* 遷移先状態 */

    /* 初期化 */
    idx = 0;

    /* エラー番号初期化 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_NONE );

    /* 状態遷移タスク有無判定 */
    if ( pTransition->task == NULL ) {
        /* タスク無し */

        /* 遷移先状態設定 */
        state = pTransition->next[ 0 ];

    } else {
        /* タスク有り */

        /* 状態遷移タスク起動 */
        state = ( pTransition->task )( pArg );
    }

    /* 遷移先状態毎に繰り返し */
    for ( idx = 0; idx < MLIB_STATE_NEXT_NUM; idx++ ) {
        /* 遷移先状態判定 */
        if ( pTransition->next[ idx ] == state ) {
            /* 一致 */

            /* 遷移先状態設定 */
            MLIB_SET_IFNOT_NULL( pNextState, state );
            pHandle->state = state;

            return MLIB_SUCCESS;
        }
    }

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_TRANS );

    return MLIB_FAILURE;
}


/******************************************************************************/

