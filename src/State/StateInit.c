/******************************************************************************/
/*                                                                            */
/* src/State/StateInit.c                                                      */
/*                                                                 2020/07/19 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <string.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibState.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/* 状態遷移表サイズ */
#define SIZEOF_TABLE ( sizeof ( MLibStateTransition_t ) )


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief         状態遷移初期化
 * @details       状態遷移ハンドルを初期化する。
 *
 * @param[in/out] *pHandle  状態遷移ハンドル
 * @param[in]     *pTable   状態遷移表
 * @param[in]     tableSize 状態遷移表サイズ
 * @param[in]     state     初期状態
 * @param[out]    *pErr     エラー要因
 *                    - MLIB_ERR_NONE  エラー無し
 *                    - MLIB_ERR_PARAM パラメータ不正
 *
 * @return        初期化結果を返す。
 * @retval        MLIB_RET_SUCCESS 正常終了
 * @retval        MLIB_RET_FAILURE 異常終了
 */
/******************************************************************************/
MLibRet_t MLibStateInit( MLibState_t                 *pHandle,
                         const MLibStateTransition_t *pTable,
                         size_t                      tableSize,
                         MLibStateNo_t               state,
                         MLibErr_t                   *pErr      )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( pHandle                      == NULL            ) ||
         ( pTable                       == NULL            ) ||
         ( ( tableSize % SIZEOF_TABLE ) != 0               ) ||
         ( state                        == MLIB_STATE_NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_SUCCESS;
    }

    /* スピンロック初期化 */
    MLibSpinInit( &( pHandle->lock ), NULL );

    /* ハンドル設定 */
    pHandle->state         = state;
    pHandle->pTable        = pTable;
    pHandle->transitionNum = tableSize / ( sizeof ( MLibStateTransition_t ) );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
