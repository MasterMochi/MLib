/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferInit.c                                            */
/*                                                                 2020/07/18 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdlib.h>
#include <string.h>

/* ライブラリヘッダ */
#include <MLib/MLibRingBuffer.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファ初期化
 * @details     リングバッファのハンドルを初期化し、リングバッファを作成する。
 *              作成したハンドルは解放するまでデータの追加や取り出しなどのリン
 *              グバッファの操作のために必要となる。
 *
 * @param[in]   *pHandle  リングバッファのハンドル
 * @param[in]   entrySize リングバッファのエントリサイズ
 * @param[in]   entryNum  リングバッファのエントリ数
 * @param[out]  *pErr     エラー要因
 *                  - MLIB_ERR_NONE     エラー無し
 *                  - MLIB_ERR_PARAM    パラメータ不正
 *                  - MLIB_ERR_NOMEMORY メモリ不足
 *
 * @return      初期化結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibRingBufferInit( MLibRingBuffer_t *pHandle,
                              size_t           entrySize,
                              size_t           entryNum,
                              MLibErr_t        *pErr      )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( pHandle   == NULL ) ||
         ( entrySize == 0    ) ||
         ( entryNum  == 0    )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* スピンロック初期化 */
    MLibSpinInit( &( pHandle->lock ), NULL );

    /* ハンドル初期化 */
    pHandle->entrySize  = entrySize;
    pHandle->entryNum   = entryNum;
    pHandle->bufferSize = entrySize * entryNum;
    pHandle->num        = 0;
    pHandle->pushIdx    = 0;
    pHandle->popIdx     = 0;
    pHandle->pBuffer    = malloc( pHandle->bufferSize );

    /* バッファ確保結果判定 */
    if ( pHandle->pBuffer == NULL ) {
        /* 失敗 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOMEMORY );

        return MLIB_RET_FAILURE;
    }

    /* バッファ初期化 */
    memset( pHandle->pBuffer, 0, pHandle->bufferSize );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
