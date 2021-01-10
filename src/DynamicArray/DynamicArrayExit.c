/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayExit.c                                        */
/*                                                                 2021/01/10 */
/* Copyright (C) 2019-2021 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* ライブラリヘッダ */
#include <MLib/MLibDynamicArray.h>
#include <MLib/MLibWrapper.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列削除
 * @details     全てのチャンクとハンドルを解放し、動的配列を削除する。
 *
 * @param[out]  *pHandle 動的配列ハンドル
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *
 * @return      初期化結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArrayExit( MLibDynamicArray_t *pHandle,
                                MLibErr_t          *pErr     )
{
    Chunk_t *pChunk;    /* チャンク */

    /* 初期化 */
    pChunk  = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* チャンク毎に繰り返す */
    while ( true ) {
        /* チャンク削除 */
        pChunk = ( Chunk_t * ) MLibListRemoveTail( &( pHandle->list ) );

        /* 削除結果判定 */
        if ( pChunk == NULL ) {
            /* チャンク無し */
            break;
        }

        /* チャンク解放 */
        MLibWrapperFree( pChunk );
    }

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
