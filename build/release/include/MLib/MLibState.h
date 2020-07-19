/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibState.h                                               */
/*                                                                 2020/07/19 */
/* Copyright (C) 2019-2020 Mochi.                                             */
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
#include <MLib/MLibSpin.h>


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/** 無効状態番号 */
#define MLIB_STATE_NULL ( 0 )

/** 無効イベント番号 */
#define MLIB_STATE_EVENT_NULL ( 0 )

/** 遷移先可能状態数 */
#define MLIB_STATE_NEXT_NUM ( 20 )

/** 状態番号型 */
typedef uint32_t MLibStateNo_t;
/** イベント番号型 */
typedef uint32_t MLibStateEvent_t;

/** 状態遷移タスク型 */
typedef MLibStateNo_t ( *MLibStateTask_t )( void *pArg );

/** 遷移先状態番号リスト型 */
typedef MLibStateEvent_t MLibStateList_t[ MLIB_STATE_NEXT_NUM ];

/** 状態遷移表エントリ型 */
typedef struct {
    MLibStateNo_t    state; /**< 状態番号             */
    MLibStateEvent_t event; /**< イベント番号         */
    MLibStateTask_t  task;  /**< 状態遷移タスク       */
    MLibStateList_t  next;  /**< 遷移先状態番号リスト */
} MLibStateTransition_t;

/** 状態遷移ハンドル型 */
typedef struct {
    MLibSpin_t                  lock;           /**< スピンロック */
    MLibStateNo_t               state;          /**< 状態         */
    const MLibStateTransition_t *pTable;        /**< 状態遷移表   */
    size_t                      transitionNum;  /**< 状態遷移数   */
} MLibState_t;


/******************************************************************************/
/* ライブラリ関数宣言                                                         */
/******************************************************************************/
/* 状態遷移実行 */
extern MLibRet_t MLibStateExec( MLibState_t      *pHandle,
                                MLibStateEvent_t event,
                                void             *pArg,
                                MLibStateNo_t    *pPrevState,
                                MLibStateNo_t    *pNextState,
                                MLibErr_t        *pErr        );
/* 状態取得 */
extern MLibStateNo_t MLibStateGet( MLibState_t *pHandle,
                                   MLibErr_t   *pErr     );
/* 状態遷移初期化 */
extern MLibRet_t MLibStateInit( MLibState_t                 *pHandle,
                                const MLibStateTransition_t *pTable,
                                size_t                      tableSize,
                                MLibStateNo_t               state,
                                MLibErr_t                   *pErr      );
/* 状態設定 */
extern MLibRet_t MLibStateSet( MLibState_t   *pHandle,
                               MLibStateNo_t state,
                               MLibErr_t     *pErr     );


/******************************************************************************/
#endif
