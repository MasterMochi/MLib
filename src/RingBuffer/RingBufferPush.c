/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferPush.c                                            */
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
 * @brief       リングバッファ追加
 * @details     リングバッファにデータを追加する。追加先インデックスがラップし、
 *              そのインデックスが指すバッファが未だ取り出されていない場合は、
 *              データを上書きする。
 *
 * @param[in]   *pHandle リングバッファのハンドル
 * @param[in]   *pData   追加するデータ
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *
 * @return      リングバッファにデータを追加した結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibRingBufferPush( MLibRingBuffer_t *pHandle,
                              const void       *pData,
                              MLibErr_t        *pErr     )
{
    char *pAddr;

    /* 初期化 */
    pAddr = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( pHandle == NULL ) ||
         ( pData   == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* バッファアドレス算出 */
    pAddr = ( ( char * ) pHandle->pBuffer ) +
            pHandle->pushIdx * pHandle->entrySize;

    /* バッファ追加 */
    memcpy( pAddr, pData, pHandle->entrySize );

    /* プッシュインデックス更新 */
    pHandle->pushIdx++;

    /* プッシュインデックスラップ判定 */
    if ( pHandle->pushIdx > pHandle->entryNum ) {
        /* ラップ */

        pHandle->pushIdx = 0;
    }

    /* ポップインデックス更新判定 */
    if ( pHandle->popIdx == pHandle->pushIdx ) {
        /* 更新 */

        pHandle->popIdx++;
    }

    /* ポップインデックスラップ判定 */
    if ( pHandle->popIdx > pHandle->entryNum ) {
        /* ラップ */

        pHandle->popIdx = 0;
    }

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
