/******************************************************************************/
/*                                                                            */
/* src/Split/SplitInit.c                                                      */
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

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibSplit.h>


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       文字列分割(区切り文字)
 * @details     区切り文字を用いて文字列を分割し、操作用のハンドルを生成する。
 *
 * @param[out]  **ppHandle ハンドル
 * @param[in]   *pStr      文字列
 * @param[in]   length     文字列文字数
 * @param[in]   delimiter  区切り文字
 * @param[out]  *pErr      エラー要因
 *                         - MLIB_ERR_NONE     エラー無し
 *                         - MLIB_ERR_PARAM    パラメータ不正
 *                         - MLIB_ERR_NOMEMORY メモリ不足
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 *
 * @note        - 文字列は必ず1文字以上あること。
 *              - 区切り文字にNULL文字は使用できない。
 *
 * @attention   - 使用済みハンドルは、MLibSplitTerm()を用いて解放すること。
 */
/******************************************************************************/
MLibRet_t MLibSplitInitByDelimiter( MLibSplit_t **ppHandle,
                                    const char  *pStr,
                                    size_t      length,
                                    char        delimiter,
                                    MLibErr_t   *pErr       )
{
    char     *pSplitStr;    /* 分割文字列             */
    uint32_t idx;           /* 文字列インデックス     */
    uint32_t splitStrNo;    /* 分割文字列番号         */
    uint32_t splitStrIdx;   /* 分割文字列インデックス */
    uint32_t delimiterNum;  /* 区切り文字数           */

    /* 初期化 */
    splitStrNo   = 0;
    splitStrIdx  = 0;
    delimiterNum = 0;

    /* エラー要因設定 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( ( ppHandle  == NULL ) ||
         ( pStr      == NULL ) ||
         ( length    == 0    ) ||
         ( delimiter == '\0' )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* 1文字毎に繰り返す */
    for ( idx = 0; idx < length; idx++ ) {
        /* NULL文字判定 */
        if ( pStr[ idx ] == '\0' ) {
            /* NULL文字 */
            break;
        }

        /* 区切り文字判定 */
        if ( pStr[ idx ] == delimiter ) {
            /* 区切り文字 */
            delimiterNum++;
        }
    }

    /* ハンドル生成 */
    *ppHandle = ( MLibSplit_t * )
                malloc( sizeof ( MLibSplit_t )                   +
                        sizeof ( char * ) * ( delimiterNum + 1 ) +
                        length + delimiterNum + 1                  );

    /* 生成結果判定 */
    if ( *ppHandle == NULL ) {
        /* 失敗 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NOMEMORY );

        return MLIB_RET_FAILURE;
    }

    /* ハンドル初期化 */
    ( *ppHandle )->num   = delimiterNum + 1;
    ( *ppHandle )->idx   = 0;
    ( *ppHandle )->ppStr = ( char ** ) ( *ppHandle )->data;
    ( *ppHandle )->pStrs = ( *ppHandle )->data +
                           sizeof ( char * ) * ( delimiterNum + 1 );
    pSplitStr            = ( *ppHandle )->pStrs;

    /* 1文字毎に繰り返し */
    for ( idx = 0; splitStrNo <= delimiterNum; idx++ ) {
        /* 文字判定 */
        if ( ( idx         == length    ) ||
             ( pStr[ idx ] == '\0'      ) ||
             ( pStr[ idx ] == delimiter )    ) {
            /* 終端、NULL文字、または、区切り文字 */

            /* NULL文字挿入 */
            ( *ppHandle )->pStrs[ splitStrIdx++ ] = '\0';

            /* 分割文字列ポインタ配列参照設定 */
            ( *ppHandle )->ppStr[ splitStrNo++ ] = pSplitStr;

            /* 分割文字列初期化 */
            pSplitStr = &( ( *ppHandle )->pStrs[ splitStrIdx ] );

        } else {
            /* その他 */

            /* 文字コピー */
            ( *ppHandle )->pStrs[ splitStrIdx++ ] = pStr[ idx ];
        }
    }

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
