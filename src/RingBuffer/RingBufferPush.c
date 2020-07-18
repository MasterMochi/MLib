/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferPush.c                                            */
/*                                                                 2020/07/18 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <string.h>

/* ライブラリヘッダ */
#include <MLib/MLibRingBuffer.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* ローカル関数宣言                                                           */
/******************************************************************************/
/* リングバッファ追加(内部関数) */
static void Push( MLibRingBuffer_t *pHandle,
                  const void       *pData    );


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファ追加(上書き禁止)
 * @details     リングバッファにデータを追加する。追加されているデータ数が上限
 *              に達している場合は、データを追加せずに失敗を返す。
 *
 * @param[in]   *pHandle リングバッファハンドル
 * @param[in]   *pData   追加するデータ
 * @param[in]   *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *                  - MLIB_ERR_FULL  バッファフル
 *
 * @return      データ追加結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 *
 * @note        本関数はスピンロックにより排他される。
 */
/******************************************************************************/
MLibRet_t MLibRingBufferPush( MLibRingBuffer_t *pHandle,
                              const void       *pData,
                              MLibErr_t        *pErr     )
{
    MLibRet_t ret;  /* 戻り値 */

    /* 初期化 */
    ret = MLIB_RET_FAILURE;

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

    /* スピンロック */
    MLibSpinLock( &( pHandle->lock ), NULL );

    /* バッファフル判定 */
    if ( ( ( pHandle->pushIdx + 1 ) == pHandle->popIdx ) ||
         ( ( pHandle->pushIdx == pHandle->entryNum ) &&
           ( pHandle->popIdx  == 0                 )    )   ) {
        /* バッファフル */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_FULL );

    } else {
        /* バッファ空き有り */

        /* リングバッファ追加 */
        Push( pHandle, pData );

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle->lock ), NULL );

    return ret;
}


/******************************************************************************/
/**
 * @brief       リングバッファ追加(上書き許可)
 * @details     リングバッファにデータを追加する。追加されているデータ数が上限
 *              に達していた場合は、最古のデータを破棄してデータを追加する。
 *
 * @param[in]   *pHandle リングバッファハンドル
 * @param[in]   *pData   追加するデータ
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *
 * @return      データ追加結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 *
 * @note        本関数はスピンロックにより排他される。
 */
/******************************************************************************/
MLibRet_t MLibRingBufferPushOW( MLibRingBuffer_t *pHandle,
                                const void       *pData,
                                MLibErr_t        *pErr     )
{
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

    /* スピンロック */
    MLibSpinLock( &( pHandle->lock ), NULL );

    /* リングバッファ追加 */
    Push( pHandle, pData );

    /* スピンアンロック */
    MLibSpinUnlock( &( pHandle->lock ), NULL );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
/* ローカル関数定義                                                           */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファ追加(内部関数)
 * @details     リングバッファにデータを追加する。追加先インデックスが取出し先
 *              インデックスに到達する場合は、最古のデータに最新のデータを上書
 *              きし、取出し先インデックスを更新する。
 *
 * @param[in]   *pHandle リングバッファハンドル
 * @param[in]   *pData   追加するデータ
 */
/******************************************************************************/
static void Push( MLibRingBuffer_t *pHandle,
                  const void       *pData    )
{
    char *pAddr;    /* データ追加先 */

    /* データ追加先アドレス算出 */
    pAddr = ( ( char * ) pHandle->pBuffer ) +
            pHandle->pushIdx * pHandle->entrySize;

    /* バッファ追加 */
    memcpy( pAddr, pData, pHandle->entrySize );

    /* 追加先インデックス更新 */
    pHandle->pushIdx++;

    /* 追加先インデックスラップ判定 */
    if ( pHandle->pushIdx > pHandle->entryNum ) {
        /* ラップ */

        /* 追加先インデックス初期化 */
        pHandle->pushIdx = 0;
    }

    /* 取出し先インデックス到達判定 */
    if ( pHandle->pushIdx == pHandle->popIdx ) {
        /* 到達 */

        /* 取出し先インデックス更新 */
        pHandle->popIdx++;

        /* 取出し先インデックスラップ判定 */
        if ( pHandle->popIdx > pHandle->entryNum ) {
            /* ラップ */

            /* 取出し先インデックス初期化 */
            pHandle->popIdx = 0;
        }

    } else {
        /* 未到達 */

        /* データ数更新 */
        pHandle->num++;
    }

    return;
}


/******************************************************************************/
