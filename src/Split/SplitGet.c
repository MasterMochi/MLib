/******************************************************************************/
/*                                                                            */
/* src/Split/SplitGet.c                                                       */
/*                                                                 2020/07/19 */
/* Copyright (C) 2019-2020 Mochi.                                             */
/*                                                                            */
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
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *                  - MLIB_ERR_INDEX インデックス無効
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGet( MLibSplit_t *pHandle,
                        uint32_t    idx,
                        char        **ppStr,
                        MLibErr_t   *pErr     )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( ppStr   == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* インデックス判定 */
    if ( pHandle->num <= idx ) {
        /* 無効 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_INDEX );

        return MLIB_RET_FAILURE;
    }

    /* 分割文字列設定 */
    *ppStr = pHandle->ppStr[ idx ];

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
/**
 * @brief       次分割文字列取得
 * @details     次の分割した文字列を取得する。
 *
 * @param[in]   *pHandle ハンドル
 * @param[out]  **ppStr  分割文字列
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *                  - MLIB_ERR_INDEX インデックス無効
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGetNext( MLibSplit_t *pHandle,
                            char        **ppStr,
                            MLibErr_t   *pErr     )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( ppStr   == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* インデックス判定 */
    if ( pHandle->num <= pHandle->idx ) {
        /* 無効 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_INDEX );

        return MLIB_RET_FAILURE;
    }

    /* 分割文字列設定 */
    *ppStr = pHandle->ppStr[ pHandle->idx++ ];

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
/**
 * @brief       分割文字列数取得
 * @details     分割した文字列の数を取得する。
 *
 * @param[in]   *pHandle ハンドル
 * @param[out]  *pNum    分割文字列数
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE  エラー無し
 *                  - MLIB_ERR_PARAM パラメータ不正
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSplitGetNum( MLibSplit_t *pHandle,
                           size_t      *pNum,
                           MLibErr_t   *pErr     )
{
    /* エラー要因設定 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータ判定 */
    if ( ( pHandle == NULL ) ||
         ( pNum    == NULL )    ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* 分割文字列数設定 */
    *pNum = pHandle->num;

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
