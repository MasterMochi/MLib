/******************************************************************************/
/*                                                                            */
/* test/DynamicArray/Alloc.c                                                  */
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
 * @brief       Alloc処理成功テスト1
 * @details     MLibDynamicArrayAlloc()の処理が成功するケースをテストする。
 *
 * @return      テスト結果を返す。
 * @retval      true  OK
 * @retval      false NG
 */
/******************************************************************************/
bool AllocSuccess1( void )
{
    char               *pBuffer;    /* 割当先           */
    uint_t             idx;         /* 配列インデックス */
    MLibErr_t          errMLib;     /* エラー要因       */
    MLibRet_t          retMLib;     /* 戻り値           */
    MLibDynamicArray_t handle;      /* ハンドル         */

    /* 初期化 */
    pBuffer = NULL;
    idx     = 0;
    errMLib = MLIB_ERR_NONE;
    retMLib = MLIB_RET_FAILURE;

    /* 初期化 */
    retMLib = MLibDynamicArrayInit( &handle, 256, 1, 512, &errMLib );

    /* 初期化結果判定 */
    if ( retMLib != MLIB_RET_SUCCESS ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x\n", retMLib, errMLib );

        return false;
    }

    /* 割り当て */
    retMLib = MLibDynamicArrayAlloc( &handle,
                                     &idx,
                                     ( void ** ) &pBuffer,
                                     &errMLib              );

    /* 割り当て結果判定 */
    if ( ( retMLib != MLIB_RET_SUCCESS ) ||
         ( pBuffer == NULL             ) ||
         ( idx     != 0                )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR(
            "ret=%d, err=%#x, idx=%u, pBuf=%p\n",
            retMLib,
            errMLib,
            idx,
            pBuffer
        );

        /* 削除 */
        MLibDynamicArrayExit( &handle, NULL );

        return false;
    }

    /* 割り当て */
    retMLib = MLibDynamicArrayAlloc( &handle,
                                     &idx,
                                     ( void ** ) &pBuffer,
                                     &errMLib              );

    /* 割り当て結果判定 */
    if ( ( retMLib != MLIB_RET_SUCCESS ) ||
         ( pBuffer == NULL             ) ||
         ( idx     != 1                )    ) {
        /* 非期待値 */

        /* NG表示 */
        CMN_ERROR( "ret=%d, err=%#x, idx=%u, pBuf=%p\n",
                retMLib,
                errMLib,
                idx,
                pBuffer
        );

        /* 削除 */
        MLibDynamicArrayExit( &handle, NULL );

        return false;
    }

    /* 削除 */
    MLibDynamicArrayExit( &handle, NULL );

    return true;
}


/******************************************************************************/
