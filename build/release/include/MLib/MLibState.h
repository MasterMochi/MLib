/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibState.h                                               */
/*                                                                 2019/06/21 */
/* Copyright (C) 2019 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_STATE_H_
#define _MLIB_STATE_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdint.h>
#include <stddef.h>

/* ライブラリヘッダ */
#include <MLib/MLib.h>


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/* エラー番号 */
#define MLIB_STATE_ERR_NONE     ( 0x00000000 )  /**< エラー無し       */
#define MLIB_STATE_ERR_PARAM    ( 0x00000001 )  /**< パラメータエラー */
#define MLIB_STATE_ERR_NO_TRANS ( 0x00000002 )  /**< 状態遷移設定無し */
#define MLIB_STATE_ERR_TRANS    ( 0x00000003 )  /**< 不正状態遷移     */

/** 無効状態番号 */
#define MLIB_STATE_NULL ( 0 )

/** 無効イベント番号 */
#define MLIB_STATE_EVENT_NULL ( 0 )

/** 遷移先可能状態数 */
#define MLIB_STATE_NEXT_NUM ( 20 )

/** 状態番号型 */
typedef uint32_t MLibState_t;
/** イベント番号型 */
typedef uint32_t MLibStateEvent_t;

/** 状態遷移タスク型 */
typedef MLibState_t ( *MLibStateTask_t )( void *pArg );

/** 遷移先状態番号リスト型 */
typedef MLibStateEvent_t MLibStateList_t[ MLIB_STATE_NEXT_NUM ];

/** 状態遷移表エントリ型 */
typedef struct {
    MLibState_t      state; /**< 状態番号             */
    MLibStateEvent_t event; /**< イベント番号         */
    MLibStateTask_t  task;  /**< 状態遷移タスク       */
    MLibStateList_t  next;  /**< 遷移先状態番号リスト */
} MLibStateTransition_t;

/** 状態遷移ハンドル型 */
typedef struct {
    MLibState_t                 state;          /**< 状態       */
    const MLibStateTransition_t *pTable;        /**< 状態遷移表 */
    size_t                      transitionNum;  /**< 状態遷移数 */
} MLibStateHandle_t;


/******************************************************************************/
/* ライブラリ関数宣言                                                         */
/******************************************************************************/
/* 状態遷移実行 */
extern MLibRet_t MLibStateExec( MLibStateHandle_t *pHandle,
                                MLibStateEvent_t  event,
                                void              *pArg,
                                MLibState_t       *pPrevState,
                                MLibState_t       *pNextState,
                                uint32_t          *pErrNo      );
/* 状態取得 */
extern MLibState_t MLibStateGet( MLibStateHandle_t *pHandle,
                                 uint32_t          *pErrNo   );

/* 状態遷移初期化 */
extern MLibRet_t MLibStateInit( MLibStateHandle_t           *pHandle,
                                const MLibStateTransition_t *pTable,
                                size_t                      tableSize,
                                MLibState_t                 state,
                                uint32_t                    *pErrNo    );

/* 状態設定 */
extern MLibRet_t MLibStateSet( MLibStateHandle_t *pHandle,
                               MLibState_t       state,
                               uint32_t          *pErrNo   );


/******************************************************************************/
#endif
