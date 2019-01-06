/******************************************************************************/
/* src/Split/SplitInit.c                                                      */
/*                                                                 2019/01/06 */
/* Copyright (C) 2019 Mochi.                                                  */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdlib.h>

/* ライブラリヘッダ */
#include <MLib.h>
#include <MLibSplit.h>


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
 * @param[out]  *pErrNo    エラー番号
 *                         - MLIB_SPLIT_ERR_NONE  エラー無し
 *                         - MLIB_SPLIT_ERR_PARAM パラメータエラー
 *                         - MLIB_SPLIT_ERR_NOMEM メモリ不足エラー
 *
 * @return      処理結果を返す。
 * @retval      MLIB_SUCCESS 成功
 * @retval      MLIB_FAILURE 失敗
 *
 * @note        - 文字列は必ず1文字以上あること。
 *              - 区切り文字にNULL文字は使用できない。
 *
 * @attention   - 使用済みハンドルは、MLibSplitTerm()を用いて解放すること。
 */
/******************************************************************************/
MLibRet_t MLibSplitInitByDelimiter( MLibSplitHandle **ppHandle,
                                    const char      *pStr,
                                    size_t          length,
                                    char            delimiter,
                                    uint32_t        *pErrNo     )
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

    /* パラメータチェック */
    if ( ( ppHandle  == NULL ) ||
         ( pStr      == NULL ) ||
         ( length    == 0    ) ||
         ( delimiter == '\0' )    ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_PARAM );

        return MLIB_FAILURE;
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
    *ppHandle = ( MLibSplitHandle * )
                malloc( sizeof ( MLibSplitHandle )               +
                        sizeof ( char * ) * ( delimiterNum + 1 ) +
                        length + delimiterNum + 1                  );

    /* 生成結果判定 */
    if ( *ppHandle == NULL ) {
        /* 失敗 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NOMEM );

        return MLIB_FAILURE;
    }

    /* ハンドル初期化 */
    ( *ppHandle )->num   = delimiterNum;
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

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NONE );

    return MLIB_SUCCESS;
}


/******************************************************************************/
