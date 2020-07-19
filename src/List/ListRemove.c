/******************************************************************************/
/*                                                                            */
/* src/List/ListRemove.c                                                      */
/*                                                                 2020/07/19 */
/* Copyright (C) 2017-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibList.h>
#include <MLib/MLibSpin.h>

/* モジュール内ヘッダ */
#include "ListRemove.h"


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       指定ノード削除
 * @details     連結リストから指定したノードを削除する。
 *
 * @param[in]   *pList 連結リスト
 * @param[in]   *pNode ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibRet_t MLibListRemove( MLibList_t     *pList,
                          MLibListNode_t *pNode  )
{
    MLibRet_t ret;  /* 戻り値 */

    /* 初期化 */
    ret = MLIB_RET_FAILURE;

    /* パラメータチェック */
    if ( ( pList == NULL ) ||
         ( pNode == NULL )    ) {
        /* 不正値 */

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 内部関数 */
    ret = ListRemove( pList, pNode );

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return ret;
}


/******************************************************************************/
/**
 * @brief       先頭ノード削除
 * @details     連結リストの先頭ノードを削除する。
 *
 * @param[in]   *pList 連結リスト
 *
 * @return      処理結果を返す。
 * @retval      NULL     正常終了（先頭ノード）
 * @retval      NULL以外 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibListNode_t *MLibListRemoveHead( MLibList_t *pList )
{
    MLibListNode_t *pNode;  /* 先頭ノード（戻り値） */

    /* 初期化 */
    pNode = NULL;

    /* 引数pListチェック */
    if ( pList == NULL ) {
        /* 不正値 */

        return NULL;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 先頭ノード取得 */
    pNode = pList->pHead;

    /* 先頭ノード有無判定 */
    if ( pNode != NULL ) {
        /* 先頭ノード有 */

        /* 連結リスト先頭ノード設定 */
        pList->pHead = pNode->pNext;

        /* 次ノード有無判定 */
        if ( pNode->pNext == NULL ) {
            /* 次ノード無 */

            /* 連結リスト最後尾ノード設定 */
            pList->pTail = NULL;

        } else {
            /* 次ノード有 */

            /* 次ノード設定 */
            pNode->pNext->pPrev = NULL;
        }

        /* 連結リストサイズ設定 */
        pList->size--;

        /* 先頭ノード設定 */
        pNode->pNext = NULL;
        pNode->pPrev = NULL;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return pNode;
}


/******************************************************************************/
/**
 * @brief       最後尾ノード削除
 * @details     連結リストの先頭ノードを削除する。
 *
 * @param[in]   *pList 連結リスト
 *
 * @return      処理結果を返す。
 * @retval      NULL     正常終了（先頭ノード）
 * @retval      NULL以外 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibListNode_t *MLibListRemoveTail( MLibList_t *pList )
{
    MLibListNode_t *pNode;  /* 先頭ノード（戻り値） */

    /* 初期化 */
    pNode = NULL;

    /* 引数pListチェック */
    if ( pList == NULL ) {
        /* 不正値 */

        return NULL;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 最後尾ノード取得 */
    pNode = pList->pTail;

    /* 最後尾ノード有無判定 */
    if ( pNode != NULL ) {
        /* 最後尾ノード有 */

        /* 連結リスト最後尾ノード設定 */
        pList->pTail = pNode->pPrev;

        /* 前ノード有無判定 */
        if ( pNode->pPrev == NULL ) {
            /* 前ノード無 */

            /* 連結リスト先頭ノード設定 */
            pList->pHead = NULL;

        } else {
            /* 前ノード有 */

            /* 前ノード設定 */
            pNode->pPrev->pNext = NULL;
        }

        /* 連結リストサイズ設定 */
        pList->size--;

        /* 最後尾ノード設定 */
        pNode->pNext = NULL;
        pNode->pPrev = NULL;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return pNode;
}


/******************************************************************************/
/* ライブラリ内ローカル関数                                                   */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       指定ノード削除(内部関数)
 * @details     連結リストから指定したノードを削除する。
 *
 * @param[in]   *pList 連結リスト
 * @param[in]   *pNode ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 */
/******************************************************************************/
MLibRet_t ListRemove( MLibList_t     *pList,
                      MLibListNode_t *pNode  )
{
    /* 連結リストサイズチェック */
    if ( pList->size == 0 ) {
        /* サイズ不正 */

        return MLIB_RET_FAILURE;
    }

    /* 連結リスト内ノード判定 */
    if ( pNode->pList != pList ) {
        /* 不正 */

        return MLIB_RET_FAILURE;
    }

    /* ノード位置判定 */
    if ( ( pNode->pPrev == NULL ) && ( pNode->pNext == NULL ) ) {
        /* 先頭かつ最後尾ノード */

        /* 連結リスト先頭・最後尾ノード設定 */
        pList->pHead = NULL;
        pList->pTail = NULL;

    } else if ( pNode->pPrev == NULL ) {
        /* 先頭ノード */

        /* 連結リスト先頭ノード設定 */
        pList->pHead = pNode->pNext;

        /* 後ノード設定 */
        pList->pHead->pPrev = NULL;

    } else if ( pNode->pNext == NULL ) {
        /* 最後尾ノード */

        /* 連結リスト最後尾ノード設定 */
        pList->pTail = pNode->pPrev;

        /* 前ノード設定 */
        pList->pTail->pNext = NULL;

    } else {
        /* 中間ノード */

        /* 前後ノード設定 */
        pNode->pNext->pPrev = pNode->pPrev;
        pNode->pPrev->pNext = pNode->pNext;
    }

    /* 削除ノード設定 */
    pNode->pNext = NULL;
    pNode->pPrev = NULL;

    /* 連結リストサイズ設定 */
    pList->size--;

    return MLIB_RET_SUCCESS;
}


/******************************************************************************/
