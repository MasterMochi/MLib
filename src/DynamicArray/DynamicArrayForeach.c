/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayForeach.c                                     */
/*                                                                 2019/10/09 */
/* Copyright (C) 2019 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdarg.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibDynamicArray.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* ローカル関数宣言                                                           */
/******************************************************************************/
/* 動的配列エントリ全操作 */
static MLibRet_t Foreach( MLibDynamicArray_t          *pHandle,
                          MLibErr_t                   *pErr,
                          MLibDynamicArrayForeachCB_t pCallback,
                          va_list                     vaList     );


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ全操作
 * @details     割当済みの各エントリ毎に引数*pCallbackが指すコールバック関数を
 *              呼び出す。
 *
 * @param[in]   *pHandle   動的配列ハンドル
 * @param[out]  *pErr      エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 * @param[in]   *pCallback コールバック関数
 * @param[in]   ...        コールバック関数可変長引数
 *
 * @return      処理結果判定
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArrayForeach( MLibDynamicArray_t          *pHandle,
                                   MLibErr_t                   *pErr,
                                   MLibDynamicArrayForeachCB_t pCallback,
                                   ...                                    )
{
    va_list   vaList;   /* 可変長引数リスト */
    MLibRet_t retMLib;  /* 戻り値           */

    /* 初期化 */
    retMLib = MLIB_RET_FAILURE;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( pHandle   == NULL ) ||
         ( pCallback == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* 可変長引数リスト初期化 */
    va_start( vaList, pCallback );

    /* 全操作 */
    retMLib = Foreach( pHandle, pErr, pCallback, vaList );

    /* 可変長引数リスト解放 */
    va_end( vaList );

    return retMLib;
}


/******************************************************************************/
/* ローカル関数定義                                                           */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ全操作(内部関数)
 * @details     割当て済みの各エントリ毎に引数*pCallbackが指すコールバック関数
 *              呼び出す。
 *
 * @param[in]   *pHandle    動的配列ハンドル
 * @param[out]  *pErr       エラー要因
 *                  - MLIB_ERR_NONE エラー無し
 * @param[in]   *pCallback  コールバック関数
 * @param[in]   vaList      コールバック関数可変長引数リスト
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 */
/******************************************************************************/
static MLibRet_t Foreach( MLibDynamicArray_t          *pHandle,
                          MLibErr_t                   *pErr,
                          MLibDynamicArrayForeachCB_t pCallback,
                          va_list                     vaList     )
{
    uint_t       localIdx;      /* チャンク内インデックス */
    Chunk_t      *pChunk;       /* チャンク               */
    ChunkEntry_t *pChunkEntry;  /* チャンクエントリ       */

    /* 初期化 */
    localIdx    = 0;
    pChunk      = NULL;
    pChunkEntry = NULL;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

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

        /* チャンク内エントリ毎に繰り返す */
        for ( localIdx = 0;
              localIdx < pHandle->chunkSize;
              localIdx++                     ) {
            /* チャンクエントリアドレス取得 */
            pChunkEntry = CHUNK_ENTRY_ADDR( pHandle, pChunk->entry, localIdx );

            /* 使用中判定 */
            if ( pChunkEntry->used == false ) {
                /* 未使用 */
                continue;
            }

            /* コールバック呼出し */
            ( pCallback )( pChunkEntry->idx,
                           pChunkEntry->pData,
                           vaList              );
        }
    }

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
