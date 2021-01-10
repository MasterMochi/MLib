/******************************************************************************/
/*                                                                            */
/* test/DynamicArray/Init.c                                                   */
/*                                                                 2021/01/10 */
/* Copyright (C) 2020-2021 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/* ライブラリヘッダ */
#include <MLib/MLibDynamicArray.h>

/* 共通ヘッダ */
#include "cmn.h"


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       Init処理失敗テスト1
 * @details     MLibDynamicArrayInit()の処理が失敗するケースをテストする。引数
 *              動的配列ハンドルにNULLを設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitFailure1( void )
{
    MLibErr_t errMLib;  /* エラー要因 */
    MLibRet_t retMLib;  /* 戻り値     */

    /* 初期化 */
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( NULL, 1, 1, 1, &errMLib );

    /* 初期化結果判定 */
    if ( ( retMLib != MLIB_RET_FAILURE ) ||
         ( errMLib != MLIB_ERR_PARAM   )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    return true;
}


/******************************************************************************/
/**
 * @brief       Init処理失敗テスト2
 * @details     MLibDynamicArrayInit()の処理が失敗するケースをテストする。引数
 *              チャンクサイズに0を設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitFailure2( void )
{
    MLibErr_t          errMLib;     /* エラー要因 */
    MLibRet_t          retMLib;     /* 戻り値     */
    MLibDynamicArray_t handle;      /* ハンドル   */

    /* 初期化 */
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 0, 1, 1, &errMLib );

    /* 初期化結果判定 */
    if ( ( retMLib != MLIB_RET_FAILURE ) ||
         ( errMLib != MLIB_ERR_PARAM   )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    return true;
}


/******************************************************************************/
/**
 * @brief       Init処理失敗テスト3
 * @details     MLibDynamicArrayInit()の処理が失敗するケースをテストする。引数
 *              エントリサイズに0を設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitFailure3( void )
{
    MLibErr_t          errMLib;     /* エラー要因 */
    MLibRet_t          retMLib;     /* 戻り値     */
    MLibDynamicArray_t handle;      /* ハンドル   */

    /* 初期化 */
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 1, 0, 1, &errMLib );

    /* 初期化結果判定 */
    if ( ( retMLib != MLIB_RET_FAILURE ) ||
         ( errMLib != MLIB_ERR_PARAM   )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    return true;
}


/******************************************************************************/
/**
 * @brief       Init処理失敗テスト4
 * @details     MLibDynamicArrayInit()の処理が失敗するケースをテストする。引数
 *              最大エントリに0を設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitFailure4( void )
{
    MLibErr_t          errMLib;     /* エラー要因 */
    MLibRet_t          retMLib;     /* 戻り値     */
    MLibDynamicArray_t handle;      /* ハンドル   */

    /* 初期化 */
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 1, 1, 0, &errMLib );

    /* 初期化結果判定 */
    if ( ( retMLib != MLIB_RET_FAILURE ) ||
         ( errMLib != MLIB_ERR_PARAM   )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    return true;
}


/******************************************************************************/
/**
 * @brief       Init処理成功テスト1
 * @details     MLibDynamicAllayInit()の処理が成功するケースをテストする。引数
 *              エラー要因には有効値を設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitSuccess1( void )
{
    MLibErr_t          errMLib;     /* エラー要因 */
    MLibRet_t          retMLib;     /* 戻り値     */
    MLibDynamicArray_t handle;      /* ハンドル   */

    /* 初期化 */
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 1, 1, 1, &errMLib );

    /* 初期化結果判定 */
    if ( retMLib != MLIB_RET_SUCCESS ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    /* 削除 */
    MLibDynamicArrayExit( &handle, NULL );

    return true;
}


/******************************************************************************/
/**
 * @brief       Init処理成功テスト2
 * @details     MLibDynamicAllayInit()の処理が成功するケースをテストする。引数
 *              エラー要因には無効値を設定する。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool InitSuccess2( void )
{
    MLibRet_t          retMLib;     /* 戻り値     */
    MLibDynamicArray_t handle;      /* ハンドル   */

    /* 初期化 */
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 1, 1, 1, NULL );

    /* 初期化結果判定 */
    if ( retMLib != MLIB_RET_SUCCESS ) {
        /* 失敗 */

        /* NG表示 */
        CMN_ERROR( "ret=%d\n", retMLib );

        return false;
    }

    /* 削除 */
    MLibDynamicArrayExit( &handle, NULL );

    return true;
}


/******************************************************************************/
