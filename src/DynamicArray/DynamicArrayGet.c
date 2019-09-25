/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayGet.c                                         */
/*                                                                 2019/09/24 */
/* Copyright (C) 2019 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdbool.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibDynamicArray.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ取得
 * @details     引数idxに該当する動的配列のエントリを取得する。
 *
 * @param[in]   *pHandle  動的配列ハンドル
 * @param[in]   idx       エントリインデックス
 * @param[out]  **ppEntry エントリアドレス
 * @param[out]  *pErr     エラー要因
 *                  - MLIB_ERR_NONE    エラー無し
 *                  - MLIB_ERR_PARAM   パラメータ不正
 *                  - MLIB_ERR_NOENTRY 該当エントリ無し
 *
 * @return      解放結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArrayGet( MLibDynamicArray_t *pHandle,
                               uint_t             idx,
                               void               **ppEntry,
                               MLibErr_t          *pErr      )
{
    uint_t  localIdx;   /* チャンク内インデックス */
    Chunk_t *pChunk;    /* チャンク               */

    /* 初期化 */
    localIdx = 0;
    pChunk   = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( pHandle == NULL ) ||
         ( ppEntry == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* チャンク毎に繰り返す */
    while ( true ) {
        /* チャンク取得 */
        pChunk = ( Chunk_t * )
                 MLibListGetNextNode( &( pHandle->list ),
                                      ( MLibListNode_t * ) pChunk );

        /* 取得結果判定 */
        if ( pChunk == NULL ) {
            /* チャンク無し */
            break;
        }

        /* チャンク内インデックス計算 */
        localIdx = idx - pChunk->entry[ 0 ].idx;

        /* チャンク内判定 */
        if ( localIdx >= pHandle->chunkSize ) {
            /* チャンク外 */
            continue;
        }

        /* 使用中判定 */
        if ( pChunk->entry[ localIdx ].used == false ) {
            /* 未使用 */
            break;
        }

        /* 出力パラメータ設定 */
        *ppEntry = pChunk->entry[ localIdx ].pData;

        return MLIB_RET_SUCCESS;
    }

    /* エラー要因設定 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOENTRY );

    return MLIB_RET_FAILURE;
}


/******************************************************************************/
