/******************************************************************************/
/* src/Split/SplitTerm.c                                                      */
/*                                                                 2019/01/13 */
/* Copyright (C) 2019 Mochi.                                                  */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdlib.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibSplit.h>


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       分割文字列取得
 * @details     分割した文字列を取得する。
 *
 * @param[in]   *pHandle ハンドル
 * @param[in]   idx      インデックス
 * @param[out]  **ppStr  分割文字列
 * @param[out]  *pErrNo  エラー番号
 *                  - MLIB_SPLIT_ERR_NONE  エラー無し
 *                  - MLIB_SPLIT_ERR_PARAM パラメータエラー
 *                  - MLIB_SPLIT_ERR_NOIDX インデックス無効エラー
 *
 * @return      処理結果を返す。
 * @retval      MLIB_SUCCESS 成功
 * @retval      MLIB_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGet( MLibSplitHandle_t *pHandle,
                        uint32_t          idx,
                        char              **ppStr,
                        uint32_t          *pErrNo   )
{
    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( ppStr   == NULL )    ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* インデックス判定 */
    if ( pHandle->num <= idx ) {
        /* 無効 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NOIDX );

        return MLIB_FAILURE;
    }

    /* 分割文字列設定 */
    *ppStr = pHandle->ppStr[ idx ];

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NONE );

    return MLIB_SUCCESS;
}


/******************************************************************************/
/**
 * @brief       次分割文字列取得
 * @details     次の分割した文字列を取得する。
 *
 * @param[in]   *pHandle ハンドル
 * @param[out]  **ppStr  分割文字列
 * @param[out]  *pErrNo  エラー番号
 *                  - MLIB_SPLIT_ERR_NONE  エラー無し
 *                  - MLIB_SPLIT_ERR_PARAM パラメータエラー
 *                  - MLIB_SPLIT_ERR_NOIDX インデックス無効エラー
 *
 * @return      処理結果を返す。
 * @retval      MLIB_SUCCESS 成功
 * @retval      MLIB_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGetNext( MLibSplitHandle_t *pHandle,
                            char              **ppStr,
                            uint32_t          *pErrNo   )
{
    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( ppStr   == NULL )    ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* インデックス判定 */
    if ( pHandle->num <= pHandle->idx ) {
        /* 無効 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NOIDX );

        return MLIB_FAILURE;
    }

    /* 分割文字列設定 */
    *ppStr = pHandle->ppStr[ pHandle->idx++ ];

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NONE );

    return MLIB_SUCCESS;
}


/******************************************************************************/
/**
 * @brief       分割文字列数取得
 * @details     分割した文字列の数を取得する。
 *
 * @param[in]   *pHandle ハンドル
 * @param[out]  *pNum    分割文字列数
 * @param[out]  *pErrNo  エラー番号
 *                  - MLIB_SPLIT_ERR_NONE  エラー無し
 *                  - MLIB_SPLIT_ERR_PARAM パラメータエラー
 *
 * @return      処理結果を返す。
 * @retval      MLIB_SUCCESS 成功
 * @retval      MLIB_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGetNum( MLibSplitHandle_t *pHandle,
                           size_t            *pNum,
                           uint32_t          *pErrNo   )
{
    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( pNum    == NULL )    ) {
        /* 不正 */

        /* エラー番号設定 */
        MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_PARAM );

        return MLIB_FAILURE;
    }

    /* 分割文字列数設定 */
    *pNum = pHandle->num;

    /* エラー番号設定 */
    MLIB_SET_IFNOT_NULL( pErrNo, MLIB_SPLIT_ERR_NONE );

    return MLIB_SUCCESS;
}


/******************************************************************************/
