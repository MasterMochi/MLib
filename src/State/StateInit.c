/******************************************************************************/
/*                                                                            */
/* src/State/StateInit.c                                                      */
/*                                                                 2019/06/21 */
/* Copyright (C) 2019 Mochi.                                                  */
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
 * @param[out]    *pErrNo   エラー番号
 *                    - MLIB_STATE_ERR_NONE  エラー無し
 *                    - MLIB_STATE_ERR_PARAM パラメータエラー
 *
 * @return        初期化結果を返す。
 * @retval        MLIB_SUCCESS 正常終了
 * @retval        MLIB_FAILURE 異常終了
 */
/******************************************************************************/
MLibRet_t MLibStateInit( MLibStateHandle_t           *pHandle,
                         const MLibStateTransition_t *pTable,
                         size_t                      tableSize,
                         MLibState_t                 state,
                         uint32_t                    *pErrNo    )
{
    /* エラー番号初期化 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_NONE );

    /* 状態遷移ハンドルチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_PARAM );

        return MLIB_SUCCESS;
    }

    /* 状態遷移表チェック */
    if ( pTable == NULL ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* 状態遷移表サイズチェック */
    if ( ( tableSize % ( sizeof ( MLibStateTransition_t ) ) ) != 0 ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* 初期状態チェック */
    if ( state == MLIB_STATE_NULL ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_STATE_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* ハンドル初期化 */
    memset( pHandle, 0, sizeof ( MLibStateHandle_t ) );

    /* ハンドル設定 */
    pHandle->state         = state;
    pHandle->pTable        = pTable;
    pHandle->transitionNum = tableSize / ( sizeof ( MLibStateTransition_t ) );

    return MLIB_SUCCESS;
}


/******************************************************************************/
