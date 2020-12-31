/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayChunk.c                                       */
/*                                                                 2020/12/31 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>

/* ライブラリヘッダ */
#include <MLib/MLibList.h>
#include <MLib/MLibDynamicArray.h>
#include <MLib/MLibWrapper.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       チャンク追加
 * @details     チャンクを追加する。
 *
 * @param[in]   *pHandle 動的配列ハンドル
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE     エラー無し
 *                  - MLIB_ERR_NOMEMORY メモリ不足
 *
 * @return      チャンクへのポインタを返す。
 * @retval      NULL     失敗
 * @retval      NULL以外 成功
 */
/******************************************************************************/
Chunk_t *ChunkAdd( MLibDynamicArray_t *pHandle,
                   MLibErr_t          *pErr     )
{
    size_t       size;          /* エントリサイズ         */
    uint_t       idx;           /* 動的配列インデックス   */
    uint_t       localIdx;      /* チャンク内インデックス */
    Chunk_t      *pLast;        /* 最後尾チャンク         */
    Chunk_t      *pChunk;       /* 追加チャンク           */
    ChunkEntry_t *pChunkEntry;  /* チャンクエントリ       */

    /* 初期化 */
    size        = sizeof ( ChunkEntry_t ) +
                  pHandle->chunkSize *
                  ( sizeof ( ChunkEntry_t ) + pHandle->entrySize );
    idx         = 0;
    pLast       = NULL;
    pChunk      = NULL;
    pChunkEntry = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* 最後尾チャンク取得 */
    pLast = ( Chunk_t * ) MLibListGetPrevNode( &( pHandle->list ), NULL );

    /* 取得結果判定 */
    if ( pLast == NULL ) {
        /* チャンク無し */

        /* 最後尾インデックス設定 */
        idx = 0;

    } else {
        /* チャンク有り */

        /* 最後尾チャンクエントリアドレス取得 */
        pChunkEntry = CHUNK_ENTRY_ADDR( pHandle,
                                        pLast->entry,
                                        pHandle->chunkSize - 1 );

        /* 最後尾インデックス取得 */
        idx = pChunkEntry->idx + 1;
    }

    /* チャンク割当 */
    pChunk = MLibWrapperMalloc( size );

    /* 割当結果判定 */
    if ( pChunk == NULL ) {
        /* 失敗 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOMEMORY );

        return NULL;
    }

    /* チャンク初期化 */
    MLibWrapperMemset( pChunk, 0, size );

    /* チャンク内エントリ毎に繰り返す */
    for ( localIdx = 0;
          localIdx < pHandle->chunkSize;
          localIdx++                     ) {
        /* チャンクエントリアドレス取得 */
        pChunkEntry = CHUNK_ENTRY_ADDR( pHandle, pChunk->entry, localIdx );

        /* エントリ情報初期化 */
        pChunkEntry->idx  = idx + localIdx;
        pChunkEntry->used = false;
    }

    /* チャンク追加 */
    MLibListInsertTail( &( pHandle->list ), &( pChunk->node ) );

    return pChunk;
}


/******************************************************************************/
