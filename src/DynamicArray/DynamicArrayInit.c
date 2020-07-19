/******************************************************************************/
/*                                                                            */
/* src/DynamicArray/DynamicArrayInit.c                                        */
/*                                                                 2020/07/19 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* ライブラリヘッダ */
#include <MLib/MLibList.h>
#include <MLib/MLibDynamicArray.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列初期化
 * @details     動的配列管理用ハンドルを割り当て、初期化する。
 *
 * @param[out]  **ppHandle  動的配列ハンドル
 * @param[in]   chunkSize   チャンクサイズ
 * @param[in]   entrySize   エントリサイズ
 * @param[in]   entryMaxNum 最大エントリ数
 * @param[out]  *pErr       エラー要因
 *                  - MLIB_ERR_NONE     エラー無し
 *                  - MLIB_ERR_PARAM    パラメータ不正
 *                  - MLIB_ERR_NOMEMORY メモリ不足
 *
 * @return      初期化結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibDynamicArrayInit( MLibDynamicArray_t **ppHandle,
                                size_t             chunkSize,
                                size_t             entrySize,
                                size_t             entryMaxNum,
                                MLibErr_t          *pErr        )
{
    MLibRet_t retMLib;  /* 戻り値 */

    /* 初期化 */
    retMLib = MLIB_RET_FAILURE;

    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( ppHandle    == NULL ) ||
         ( chunkSize   == 0    ) ||
         ( entrySize   == 0    ) ||
         ( entryMaxNum == 0    )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* ハンドル割当 */
    *ppHandle = malloc( sizeof ( MLibDynamicArray_t ) );

    /* 割当結果判定 */
    if ( *ppHandle == NULL ) {
        /* 失敗 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOMEMORY );

        return MLIB_RET_FAILURE;
    }

    /* ハンドル初期化 */
    memset( *ppHandle, 0, sizeof ( MLibDynamicArray_t ) );
    ( *ppHandle )->chunkSize   = chunkSize;
    ( *ppHandle )->entrySize   = entrySize;
    ( *ppHandle )->entryMaxNum = entryMaxNum;
    ( *ppHandle )->entryNum    = 0;

    /* リンクリスト初期化 */
    retMLib = MLibListInit( &( ( *ppHandle )->list ) );

    return retMLib;
}


/******************************************************************************/
