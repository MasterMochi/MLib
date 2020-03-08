/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferPop.c                                             */
/*                                                                 2020/03/02 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <string.h>

/* ライブラリヘッダ */
#include <MLib/MLibRingBuffer.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファ取り出し
 * @details     リングバッファからデータを取り出す。
 *
 * @param[in]   *pHandle リングバッファのハンドル
 * @param[out]  *pData   取り出し先データ
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE    エラー無し
 *                  - MLIB_ERR_PARAM   パラメータ不正
 *                  - MLIB_ERR_NOENTRY エントリ無し
 *
 * @return      リングバッファからデータを取り出した結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibRingBufferPop( MLibRingBuffer_t *pHandle,
                             void             *pData,
                             MLibErr_t        *pErr     )
{
    char *pAddr;

    /* 初期化 */
    pAddr = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* バッファ有無判定 */
    if ( pHandle->popIdx == pHandle->pushIdx ) {
        /* バッファ無し */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOENTRY );

        return MLIB_RET_FAILURE;
    }

    /* バッファアドレス算出 */
    pAddr = ( ( char * ) pHandle->pBuffer ) +
            pHandle->popIdx * pHandle->entrySize;

    /* 取り出し先データ判定 */
    if ( pData != NULL ) {
        /* 有り */

        /* バッファ取り出し */
        memcpy( pData, pAddr, pHandle->entrySize );
    }

    /* ポップインデックス更新 */
    pHandle->popIdx++;

    /* ポップインデックスラップ判定 */
    if ( pHandle->popIdx > pHandle->entryNum ) {
        /* ラップ */

        pHandle->popIdx = 0;
    }

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
