/******************************************************************************/
/*                                                                            */
/* src/List/ListRemove.h                                                      */
/*                                                                 2020/07/19 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
#ifndef LIST_REMOVE_H
#define LIST_REMOVE_H
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* ライブラリヘッダ */
#include <MLib/MLibList.h>


/******************************************************************************/
/* モジュール内ローカル関数宣言                                               */
/******************************************************************************/
/* 指定ノード削除(内部関数) */
extern MLibRet_t ListRemove( MLibList_t     *pList,
                             MLibListNode_t *pNode  );


/******************************************************************************/
#endif
