/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibDynamicArray.h                                        */
/*                                                                 2021/01/31 */
/* Copyright (C) 2017-2021 Mochi                                              */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_DYNAMICARRAY_H_
#define _MLIB_DYNAMICARRAY_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

/* ライブラリヘッダ */
#include "MLib.h"
#include "MLibList.h"


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/** 動的配列ハンドル */
typedef struct {
    MLibList_t list;        /**< リスト         */
    size_t     chunkSize;   /**< チャンクサイズ */
    size_t     entrySize;   /**< エントリサイズ */
    size_t     entryMaxNum; /**< エントリ最大数 */
    size_t     entryNum;    /**< エントリ数     */
} MLibDynamicArray_t;

/** 検索コールバック関数 */
typedef bool ( *MLibDynamicArraySearchCB_t )( uint_t  idx,
                                              void    *pEntry,
                                              va_list vaList   );

/** 全操作コールバック関数 */
typedef void ( *MLibDynamicArrayForeachCB_t )( uint_t   idx,
                                               void     *pEntry,
                                               va_list  vaList   );


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/* 動的配列エントリ割当 */
extern MLibRet_t MLibDynamicArrayAlloc(
                     MLibDynamicArray_t *pHandle,
                     uint_t             *pIdx,
                     void               **ppEntry,
                     MLibErr_t          *pErr       );
/* 動的配列エントリ割当(インデックス指定) */
extern MLibRet_t MLibDynamicArrayAllocSpec(
                     MLibDynamicArray_t *pHandle,
                     uint_t             idx,
                     void               **ppEntry,
                     MLibErr_t          *pErr      );
/* 動的配列削除 */
extern MLibRet_t MLibDynamicArrayExit(
                     MLibDynamicArray_t *pHandle,
                     MLibErr_t          *pErr     );
/* 動的配列エントリ全操作 */
extern MLibRet_t MLibDynamicArrayForeach(
                     MLibDynamicArray_t          *pHandle,
                     MLibErr_t                   *pErr,
                     MLibDynamicArrayForeachCB_t pCallback,
                     ...                                    );
/* 動的配列エントリ解放 */
extern MLibRet_t MLibDynamicArrayFree(
                     MLibDynamicArray_t *pHandle,
                     uint_t             idx,
                     MLibErr_t          *pErr     );
/* 動的配列エントリ取得 */
extern MLibRet_t MLibDynamicArrayGet(
                     MLibDynamicArray_t *pHandle,
                     uint_t             idx,
                     void               **ppEntry,
                     MLibErr_t          *pErr      );
/* 動的配列初期化 */
extern MLibRet_t MLibDynamicArrayInit(
                     MLibDynamicArray_t *pHandle,
                     size_t             chunkSize,
                     size_t             entrySize,
                     size_t             entryMaxNum,
                     MLibErr_t          *pErr        );
/* 動的配列エントリ線形検索 */
extern MLibRet_t MLibDynamicArraySearch(
                     MLibDynamicArray_t         *pHandle,
                     uint_t                     *pIdx,
                     void                       **ppEntry,
                     MLibErr_t                  *pErr,
                     MLibDynamicArraySearchCB_t pCallback,
                     ...                                   );


/******************************************************************************/
#endif
