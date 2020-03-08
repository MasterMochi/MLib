/******************************************************************************/
/*                                                                            */
/* MLib/MLibRingBuffer.h                                                      */
/*                                                                 2020/03/02 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_RINGBUFFER_H_
#define _MLIB_RINGBUFFER_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdint.h>

/* ライブラリヘッダ */
#include "MLib.h"


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/* リングバッファハンドル */
typedef struct {
    size_t   entrySize;     /**< エントリサイズ       */
    size_t   entryNum;      /**< エントリ数           */
    size_t   bufferSize;    /**< バッファサイズ       */
    uint32_t pushIdx;       /**< プッシュインデックス */
    uint32_t popIdx;        /**< ポップインデックス   */
    void     *pBuffer;      /**< バッファ             */
} MLibRingBuffer_t;


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/* リングバッファ削除 */
extern MLibRet_t MLibRingBufferExit( MLibRingBuffer_t *pHandle,
                                     MLibErr_t        *pErr     );

/* リングバッファハンドル初期化 */
extern MLibRet_t MLibRingBufferInit( MLibRingBuffer_t *pHandle,
                                     size_t           entrySize,
                                     size_t           entryNum,
                                     MLibErr_t        *pErr      );

/* リングバッファ取り出し */
extern MLibRet_t MLibRingBufferPop( MLibRingBuffer_t *pHandle,
                                    void             *pData,
                                    MLibErr_t        *pErr     );

/* リングバッファ追加 */
extern MLibRet_t MLibRingBufferPush( MLibRingBuffer_t *pHandle,
                                     const void       *pData,
                                     MLibErr_t        *pErr     );


/******************************************************************************/
#endif
