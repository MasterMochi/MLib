/******************************************************************************/
/*                                                                            */
/* src/List/ListInsert.c                                                      */
/*                                                                 2020/07/19 */
/* Copyright (C) 2017-2020 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdint.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>
#include <MLib/MLibList.h>
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       ノード先頭挿入
 * @details     指定した連結リストの先頭に新しいノードを挿入する。
 *
 * @param[in]   *pList    連結リスト
 * @param[in]   *pNewNode 挿入ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibRet_t MLibListInsertHead( MLibList_t     *pList,
                              MLibListNode_t *pNewNode )
{
    MLibRet_t      ret;         /* 戻り値       */
    MLibListNode_t *pOldHead;   /* 旧先頭ノード */

    /* 初期化 */
    ret      = MLIB_RET_FAILURE;
    pOldHead = NULL;

    /* パラメータチェック */
    if ( ( pList    == NULL ) ||
         ( pNewNode == NULL )    ) {
        /* 不正値 */

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 連結リストサイズチェック */
    if ( pList->size != SIZE_MAX ) {
        /* 空き有り */

        /* 旧先頭ノード取得 */
        pOldHead = pList->pHead;

        /* 連結リスト先頭ノード設定 */
        pList->pHead = pNewNode;

        /* 挿入ノード設定 */
        pNewNode->pList = pList;
        pNewNode->pNext = pOldHead;
        pNewNode->pPrev = NULL;

        /* 旧先頭ノード有無判定 */
        if ( pOldHead == NULL ) {
            /* 旧先頭ノード無 */

            /* 連結リスト最後尾ノード設定 */
            pList->pTail = pNewNode;

        } else {
            /* 旧先頭ノード有 */

            /* 旧先頭ノード設定 */
            pOldHead->pPrev = pNewNode;
        }

        /* 連結リストサイズ設定 */
        pList->size++;

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return ret;
}


/******************************************************************************/
/**
 * @brief       ノード次挿入
 * @details     指定したノードの次に新しいノードを挿入する。
 *
 * @param[in]   *pList    連結リスト
 * @param[in]   *pNode    挿入先ノード
 * @param[in]   *pNewNode 挿入ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibRet_t MLibListInsertNext( MLibList_t     *pList,
                              MLibListNode_t *pNode,
                              MLibListNode_t *pNewNode )
{
    MLibRet_t      ret;         /* 戻り値   */
    MLibListNode_t *pNextNode;  /* 次ノード */

    /* 初期化 */
    ret       = MLIB_RET_FAILURE;
    pNextNode = NULL;

    /* 先頭指定チェック */
    if ( pNode == NULL ) {
        /* 先頭指定 */

        return MLibListInsertHead( pList, pNewNode );
    }

    /* パラメータチェック */
    if ( ( pList    == NULL ) ||
         ( pNewNode == NULL )    ) {
        /* 不正値 */

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 連結リストサイズチェック */
    if ( ( pList->size != 0 ) && ( pList->size != SIZE_MAX ) ) {
        /* 1つ以上ノード有かつ空き有 */

        /* 次ノード取得 */
        pNextNode = pNode->pNext;

        /* 前ノード設定 */
        pNode->pNext = pNewNode;

        /* 挿入ノード設定 */
        pNewNode->pList = pList;
        pNewNode->pPrev = pNode;
        pNewNode->pNext = pNextNode;

        /* 次ノード有無判定 */
        if ( pNextNode == NULL ) {
            /* 次ノード無 */

            /* 連結リスト最後尾ノード設定 */
            pList->pTail = pNewNode;

        } else {
            /* 次ノード有 */

            /* 次ノード設定 */
            pNextNode->pPrev = pNewNode;
        }

        /* 連結リストサイズ設定 */
        pList->size++;

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return ret;
}


/******************************************************************************/
/**
 * @brief       ノード前挿入
 * @details     指定したノードの前に新しいノードを挿入する。
 *
 * @param[in]   *pList    連結リスト
 * @param[in]   *pNode    挿入先ノード
 * @param[in]   *pNewNode 挿入ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibRet_t MLibListInsertPrev( MLibList_t     *pList,
                              MLibListNode_t *pNode,
                              MLibListNode_t *pNewNode )
{
    MLibRet_t      ret;         /* 戻り値   */
    MLibListNode_t *pPrevNode;  /* 前ノード */

    /* 初期化 */
    ret       = MLIB_RET_FAILURE;
    pPrevNode = NULL;

    /* 最後尾指定チェック */
    if ( pNode == NULL ) {
        /* 最後尾指定 */

        return MLibListInsertTail( pList, pNewNode );
    }

    /* パラメータチェック */
    if ( ( pList    == NULL ) ||
         ( pNewNode == NULL )    ) {
        /* 不正値 */

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 連結リストサイズチェック */
    if ( ( pList->size != 0 ) && ( pList->size != SIZE_MAX ) ) {
        /* 1つ以上ノード有かつ空き有 */

        /* 前ノード取得 */
        pPrevNode = pNode->pPrev;

        /* 次ノード設定 */
        pNode->pPrev = pNewNode;

        /* 挿入ノード設定 */
        pNewNode->pList = pList;
        pNewNode->pNext = pNode;
        pNewNode->pPrev = pPrevNode;

        /* 前ノード有無判定 */
        if ( pPrevNode == NULL ) {
            /* 前ノード無 */

            /* 連結リスト先頭ノード設定 */
            pList->pHead = pNewNode;

        } else {
            /* 前ノード有 */

            /* 前ノード設定 */
            pPrevNode->pNext = pNewNode;
        }

        /* 連結リストサイズ設定 */
        pList->size++;

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return ret;
}


/******************************************************************************/
/**
 * @brief       ノード最後尾挿入
 * @details     指定した連結リストの最後尾に新しいノードを挿入する。
 *
 * @param[in]   *pList    連結リスト
 * @param[in]   *pNewNode 挿入ノード
 *
 * @return      処理結果を返す。
 * @retval      MLIB_RET_SUCCESS 正常終了
 * @retval      MLIB_RET_FAILURE 異常終了
 *
 * @note        本関数はスピンロックを用いて排他制御する。
 */
/******************************************************************************/
MLibRet_t MLibListInsertTail( MLibList_t     *pList,
                              MLibListNode_t *pNewNode )
{
    MLibRet_t      ret;         /* 戻り値       */
    MLibListNode_t *pOldTail;   /* 最後尾ノード */

    /* 初期化 */
    ret      = MLIB_RET_FAILURE;
    pOldTail = NULL;

    /* パラメータチェック */
    if ( ( pList    == NULL ) ||
         ( pNewNode == NULL )    ) {
        /* 不正値 */

        return MLIB_RET_FAILURE;
    }

    /* スピンロック */
    MLibSpinLock( &( pList->lock ), NULL );

    /* 連結リストサイズチェック */
    if ( pList->size != SIZE_MAX ) {
        /* 空き有 */

        /* 旧最後尾ノード取得 */
        pOldTail = pList->pTail;

        /* 連結リスト最後尾ノード設定 */
        pList->pTail = pNewNode;

        /* 挿入ノード設定 */
        pNewNode->pList = pList;
        pNewNode->pNext = NULL;
        pNewNode->pPrev = pOldTail;

        /* 旧最後尾ノード有無判定 */
        if ( pOldTail == NULL ) {
            /* 旧最後尾ノード無 */

            /* 連結リスト先頭ノード設定 */
            pList->pHead = pNewNode;

        } else {
            /* 旧最後尾ノード有 */

            /* 旧最後尾ノード設定 */
            pOldTail->pNext = pNewNode;
        }

        /* 連結リストサイズ設定 */
        pList->size++;

        /* 戻り値設定 */
        ret = MLIB_RET_SUCCESS;
    }

    /* スピンアンロック */
    MLibSpinUnlock( &( pList->lock ), NULL );

    return ret;
}


/******************************************************************************/
