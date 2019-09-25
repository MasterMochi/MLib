/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArraySearch.c                                      */
/*                                                                 2019/09/25 */
/* Copyright (C) 2019 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdarg.h>
#include <stdbool.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibDynamicArray.h>

/* モジュールヘッダ */
#include "DynamicArrayChunk.h"


/******************************************************************************/
/* ローカル関数宣言                                                           */
/******************************************************************************/
/* 動的配列エントリ線形検索 */
static MLibRet_t Search( MLibDynamicArray_t         *pHandle,
                         uint_t                     *pIdx,
                         void                       **ppEntry,
                         MLibErr_t                  *pErr,
                         MLibDynamicArraySearchCB_t pCallback,
                         va_list                    vaList      );


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ線形検索
 * @details     割当済みの各エントリ毎に引数*pCallbackが指すコールバック関数を
 *              呼び出す。コールバック関数は検索対象のエントリかどうかを判定し
 *              て、最初に検索対象としたエントリを返す。
 *
 * @param[in]   *pHandle   動的配列ハンドル
 * @param[in]   *pIdx      エントリインデックス
 * @param[in]   **ppEntry  エントリアドレス
 * @param[in]   *pErr      エラー要因
 *                  - MLIB_ERR_NONE    エラー無し
 *                  - MLIB_ERR_PARAM   パラメータ不正
 *                  - MLIB_ERR_NOENTRY 該当エントリ無し
 * @param[in]   *pCallback コールバック関数
 * @param[in]   ...        コールバック関数可変長引数
 *
 * @return      検索結果判定
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArraySearch( MLibDynamicArray_t         *pHandle,
                                  uint_t                     *pIdx,
                                  void                       **ppEntry,
                                  MLibErr_t                  *pErr,
                                  MLibDynamicArraySearchCB_t pCallback,
                                  ...                                   )
{
    va_list   vaList;   /* 可変長引数リスト */
    MLibRet_t retMLib;  /* 戻り値           */

    /* パラメータチェック */
    if ( ( pHandle   == NULL ) ||
         ( pIdx      == NULL ) ||
         ( ppEntry   == NULL ) ||
         ( pCallback == NULL )    ) {
        /* パラメータ不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* 出力パラメータ初期化 */
    *ppEntry = NULL;
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* 可変長引数リスト初期化 */
    va_start( vaList, pCallback );

    /* 検索 */
    retMLib = Search( pHandle,
                      pIdx,
                      ppEntry,
                      pErr,
                      pCallback,
                      vaList     );

    /* 可変長引数リスト解放 */
    va_end( vaList );

    return retMLib;
}


/******************************************************************************/
/* ローカル関数定義                                                           */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列エントリ線形検索(内部関数)
 * @details     割当済みの各エントリ毎に引数*pCallbackが指すコールバック関数を
 *              呼び出す。コールバック関数は検索対象のエントリかどうかを判定し
 *              て、最初に検索対象としたエントリを返す。
 *
 * @param[in]   *pHandle   動的配列ハンドル
 * @param[in]   *pIdx      エントリインデックス
 * @param[in]   **ppEntry  エントリアドレス
 * @param[in]   *pErr      エラー要因
 *                  - MLIB_ERR_NONE    エラー無し
 *                  - MLIB_ERR_NOENTRY 該当エントリ無し
 * @param[in]   *pCallback コールバック関数
 * @param[in]   vaList     コールバック関数可変長引数リスト
 *
 * @return      検索結果判定
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
static MLibRet_t Search( MLibDynamicArray_t         *pHandle,
                         uint_t                     *pIdx,
                         void                       **ppEntry,
                         MLibErr_t                  *pErr,
                         MLibDynamicArraySearchCB_t pCallback,
                         va_list                    vaList      )
{
    bool    ret;        /* 条件判定結果           */
    uint_t  localIdx;   /* チャンク内インデックス */
    Chunk_t *pChunk;    /* チャンク               */

    /* 初期化 */
    ret      = false;
    localIdx = 0;
    pChunk   = NULL;

    /* チャンク毎に繰り返す */
    while ( true ) {
        /* チャンク取得 */
        pChunk = ( Chunk_t * )
                 MLibListGetNextNode( &( pHandle->list ),
                                      ( MLibListNode_t * ) pChunk );

        /* 取得結果判定 */
        if ( pChunk == NULL ) {
            /* チャンク無し */

            /* エラー要因設定 */
            MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOENTRY );

            return MLIB_RET_FAILURE;
        }

        /* チャンク内エントリ毎に繰り返す */
        for ( localIdx = 0;
              localIdx < pHandle->chunkSize;
              localIdx++                     ) {
            /* 使用中判定 */
            if ( pChunk->entry[ localIdx ].used == false ) {
                /* 未使用 */
                continue;
            }

            /* コールバック呼出し */
            ret = ( pCallback )( pChunk->entry[ localIdx ].idx,
                                 pChunk->entry[ localIdx ].pData,
                                 vaList                           );

            /* 呼出し結果判定 */
            if ( ret != false ) {
                /* 検索対象 */

                /* 出力パラメータ設定 */
                *pIdx    = pChunk->entry[ localIdx ].idx;
                *ppEntry = pChunk->entry[ localIdx ].pData;

                return MLIB_RET_SUCCESS;
            }
        }
    }
}


/******************************************************************************/
