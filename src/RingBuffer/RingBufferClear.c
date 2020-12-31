/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferClear.c                                           */
/*                                                                 2020/07/18 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLibRingBuffer.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファクリア
 * @details     リングバッファのデータをクリアする。
 *
 * @param[in]   *pHandle  リングバッファのハンドル
 * @param[out]  *pErr     エラー要因
 *                  - MLIB_ERR_NONE     エラー無し
 *                  - MLIB_ERR_PARAM    パラメータ不正
 *
 * @return      初期化結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 *
 * @note        本関数はスピンロックによって排他される。
 */
/******************************************************************************/
MLibRet_t MLibRingBufferClear( MLibRingBuffer_t *pHandle,
                               MLibErr_t        *pErr      )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pHandle->lock ), NULL );

    /* バッファクリア */
    pHandle->num     = 0;
    pHandle->pushIdx = 0;
    pHandle->popIdx  = 0;

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle->lock ), NULL );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
