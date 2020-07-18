/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferPop.c                                             */
/*                                                                 2020/07/18 */
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
#include <MLib/MLibSpin.h>


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
 *
 * @note        本関数はスピンロックによって排他される。
 */
/******************************************************************************/
MLibRet_t MLibRingBufferPop( MLibRingBuffer_t *pHandle,
                             void             *pData,
                             MLibErr_t        *pErr     )
{
    char      *pAddr;   /* バッファアドレス */
    MLibRet_t ret;      /* 戻り値           */

    /* 初期化 */
    pAddr = NULL;
    ret   = MLIB_RET_FAILURE;

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

    /* バッファ有無判定 */
    if ( pHandle->popIdx == pHandle->pushIdx ) {
        /* バッファ無し */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOENTRY );

    } else {
        /* バッファ有り */

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

        /* データ数更新 */
        pHandle->num--;

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle->lock ), NULL );

    return ret;
}


/******************************************************************************/
