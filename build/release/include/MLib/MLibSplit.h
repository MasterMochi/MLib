/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibSplit.h                                               */
/*                                                                 2020/07/19 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_SPLIT_H_
#define _MLIB_SPLIT_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>

/* ライブラリヘッダ */
#include "MLib.h"


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/* 文字列分割ハンドル */
typedef struct {
    size_t   num;       /**< 分割文字列数                 */
    uint32_t idx;       /**< 操作中分割文字列インデックス */
    char     **ppStr;   /**< 分割文字列ポインタ配列参照   */
    char     *pStrs;    /**< 分割文字列格納先参照         */
    char     data[];    /**< データ領域                   */
} MLibSplit_t;


/******************************************************************************/
/* グローバル関数プロトタイプ宣言                                             */
/******************************************************************************/
/* 分割文字列取得 */
extern MLibRet_t MLibSplitGet( MLibSplit_t *pHandle,
                               uint32_t    idx,
                               char        **ppStr,
                               MLibErr_t   *pErr     );
/* 次分割文字列取得 */
extern MLibRet_t MLibSplitGetNext( MLibSplit_t *pHandle,
                                   char        **ppStr,
                                   MLibErr_t   *pErr     );
/* 分割文字列数取得 */
extern MLibRet_t MLibSplitGetNum( MLibSplit_t *pHandle,
                                  size_t      *pNum,
                                  MLibErr_t   *pErrNo   );
/* 文字列分割(区切り文字) */
extern MLibRet_t MLibSplitInitByDelimiter( MLibSplit_t **ppHandle,
                                           const char  *pStr,
                                           size_t      length,
                                           char        delimiter,
                                           MLibErr_t   *pErrNo     );
/* 文字列分割終了処理 */
extern MLibRet_t MLibSplitTerm( MLibSplit_t **ppHandle,
                                MLibErr_t   *pErrNo     );


/******************************************************************************/
#endif
