/******************************************************************************/
/*                                                                            */
/* src/List/ListSearch.c                                                      */
/*                                                                 2019/11/18 */
/* Copyright (C) 2019 Mochi.                                                  */
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


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       連結リスト線形検索
 * @details     連結リスト内の各ノード毎にコールバック関数*pCallbackを呼び出す。
 *              コールバック関数は検索対象のエントリかどうかを判定して、最初に
 *              対象と判定したノードを返す。
 *
 * @param[in]   *pList     連結リスト
 * @param[in]   *pCallback コールバック関数
 * @param[in]   *pParam    コールバック関数パラメータ
 * @param[in]   method     処理方式
 *                  - MLIB_LIST_GET    ノード取得
 *                  - MLIB_LIST_REMOVE ノード削除
 *
 * @return      該当ノードを返す。
 * @retval      NULL     該当ノード無
 * @retval      NULL以外 該当ノード有
 */
/******************************************************************************/
MLibListNode_t *MLibListSearchHead( MLibList_t             *pList,
                                    MLibListSearchCB_t     pCallback,
                                    void                   *pParam,
                                    MLibListSearchMethod_t method     )
{
    bool           ret;     /* 判定結果 */
    MLibListNode_t *pNode;  /* ノード   */

    /* パラメータチェック */
    if ( ( pList     == NULL ) ||
         ( pCallback == NULL )    ) {
        /* パラメータ不正 */

        return NULL;
    }

    /* 初期化 */
    ret   = MLIB_RET_FAILURE;
    pNode = pList->pHead;

    /* ノード毎に繰り返す */
    while ( pNode != NULL ) {
        /* コールバック関数呼出し */
        ret = ( pCallback )( pNode, pParam );

        /* 呼出し結果判定 */
        if ( ret == false ) {
            /* 非対象 */

            /* 次ノード */
            pNode = pNode->pNext;
            continue;
        }

        /* 処理方式判定 */
        if ( method == MLIB_LIST_REMOVE ) {
            /* 削除 */

            MLibListRemove( pList, pNode );
        }

        return pNode;
    }

    return NULL;
}


/******************************************************************************/
