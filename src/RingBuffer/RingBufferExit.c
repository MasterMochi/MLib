/******************************************************************************/
/*                                                                            */
/* src/RingBuffer/RingBufferExit.c                                            */
/*                                                                 2020/12/31 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLibRingBuffer.h>
#include <MLib/MLibWrapper.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファ削除
 * @details     リングバッファを解放してハンドルの使用を終了する。
 *
 * @param[in]   *pHandle リングバッファのハンドル
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *
 * @return      削除結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibRingBufferExit( MLibRingBuffer_t *pHandle,
                              MLibErr_t        *pErr     )
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

    /* バッファ解放 */
    MLibWrapperFree( pHandle->pBuffer );

    /* ハンドル初期化 */
    MLibWrapperMemset( pHandle, 0, sizeof ( MLibRingBuffer_t ) );

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
