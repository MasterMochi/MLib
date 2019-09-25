/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayAlloc.c                                       */
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
#include <MLib/MLibList.h>
#include <MLib/MLibDynamicArray.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ割当
 * @details     動的配列のエントリを割当てる。
 *
 * @param[in]   *pHandle  動的配列ハンドル
 * @param[out]  *pIdx     エントリインデックス
 * @param[out]  **ppEntry エントリアドレス
 * @param[out]  *pErr     エラー要因
 *                  - MLIB_ERR_NONE      エラー無し
 *                  - MLIB_ERR_PARAM     パラメータ不正
 *                  - MLIB_ERR_NOMEMORY  メモリ不足
 *                  - MLIB_ERR_LIMITOVER 割当上限超過
 *
 * @return      割当結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArrayAlloc( MLibDynamicArray_t *pHandle,
                                 uint_t             *pIdx,
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
         ( pIdx    == NULL ) ||
         ( ppEntry == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* エントリ数チェック */
    if ( pHandle->entryNum >= pHandle->entryMaxNum ) {
        /* 上限 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_LIMITOVER );

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

            /* チャンク追加 */
            pChunk = ChunkAdd( pHandle, pErr );

            /* 追加結果判定 */
            if ( pChunk == NULL ) {
                /* 失敗 */
                return MLIB_RET_FAILURE;
            }
        }

        /* エントリ毎に繰り返す */
        for ( localIdx = 0;
              localIdx < pHandle->chunkSize;
              localIdx++                     ) {
            /* 未使用判定 */
            if ( pChunk->entry[ localIdx ].used == false ) {
                /* 未使用 */

                /* 割当設定 */
                pHandle->entryNum++;
                pChunk->entry[ localIdx ].used = true;

                /* 出力パラメータ設定 */
                *pIdx    = pChunk->entry[ localIdx ].idx;
                *ppEntry = pChunk->entry[ localIdx ].pData;

                return MLIB_RET_SUCCESS;
            }
        }
    }
}


/******************************************************************************/
