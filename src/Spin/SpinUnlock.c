/******************************************************************************/
/*                                                                            */
/* src/Spin/SpinUnlock.c                                                      */
/*                                                                 2020/07/14 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       スピンアンロック
 * @details     スピンアンロックする。
 *
 * @param[in]   *pHandle スピンロックハンドル
 * @param[out]  *pErr    エラー要因
 *                  - MLIB_ERR_NONE     エラー無し
 *                  - MLIB_ERR_PARAM    パラメータ不正
 *
 * @return      初期化結果を返す。
 * @retval      MLIB_RET_SUCCESS 成功
 * @retval      MLIB_RET_FAILURE 失敗
 */
/******************************************************************************/
MLibRet_t MLibSpinUnlock( MLibSpin_t *pHandle,
                          MLibErr_t  *pErr     )
{
    /* エラー要因初期化 */
    MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_NONE );

    /* パラメータチェック */
    if ( pHandle == NULL ) {
        /* 不正 */

        /* エラー要因設定 */
        MLIB_SET_IFNOT_NULL( pErr, MLIB_ERR_PARAM );

        return MLIB_RET_FAILURE;
    }

    /* アンロック */
    __asm__ __volatile__ (
        "mov  eax, 0;"              /* アンロック値   */
        "xchg eax, %0"              /* アンロック     */
        :                           /* 出力オペランド */
        : "m" ( pHandle->lock )     /* 入力オペランド */
        : "eax"                 );  /* 破壊レジスタ   */

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
