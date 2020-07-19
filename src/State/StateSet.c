/******************************************************************************/
/*                                                                            */
/* src/State/StateSet.c                                                       */
/*                                                                 2020/07/19 */
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
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief           状態設定
 * @details         状態を設定する。
 *
 * @param[in/out]   *pHandle 状態遷移ハンドル
 * @param[in]       state    状態
 * @param[out]      *pErr    エラー要因
 *                      - MLIB_ERR_NONE  エラー無し
 *                      - MLIB_ERR_PARAM パラメータ不正
 *
 * @return          処理結果を返す。
 * @retval          MLIB_RET_SUCCESS 正常終了
 * @retval          MLIB_RET_FAILURE 異常終了
 *
 * @note            本関数はスピンロックを用いて排他する。
 */
/******************************************************************************/
MLibRet_t MLibStateSet( MLibState_t   *pHandle,
                        MLibStateNo_t state,
                        MLibErr_t     *pErr     )
{
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

    /* 状態設定 */
    pHandle->state = state;

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle-> lock ), NULL );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
