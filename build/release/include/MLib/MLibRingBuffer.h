/******************************************************************************/
/*                                                                            */
/* MLib/MLibRingBuffer.h                                                      */
/*                                                                 2020/07/18 */
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
#include "MLibSpin.h"


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/* リングバッファハンドル */
typedef struct {
    MLibSpin_t lock;        /**< スピンロック         */
    size_t     entrySize;   /**< エントリサイズ       */
    size_t     entryNum;    /**< エントリ数           */
    size_t     bufferSize;  /**< バッファサイズ       */
    size_t     num;         /**< データ数             */
    uint32_t   pushIdx;     /**< プッシュインデックス */
    uint32_t   popIdx;      /**< ポップインデックス   */
    void       *pBuffer;    /**< バッファ             */
} MLibRingBuffer_t;


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/* リングバッファクリア */
extern MLibRet_t MLibRingBufferClear( MLibRingBuffer_t *pHandle,
                                      MLibErr_t        *pErr     );
/* リングバッファ削除 */
extern MLibRet_t MLibRingBufferExit( MLibRingBuffer_t *pHandle,
                                     MLibErr_t        *pErr     );
/* リングバッファハンドル初期化 */
extern MLibRet_t MLibRingBufferInit( MLibRingBuffer_t *pHandle,
                                     size_t           entrySize,
                                     size_t           entryNum,
                                     MLibErr_t        *pErr      );
/* リングバッファ取出 */
extern MLibRet_t MLibRingBufferPop( MLibRingBuffer_t *pHandle,
                                    void             *pData,
                                    MLibErr_t        *pErr     );
/* リングバッファ追加(上書き禁止) */
extern MLibRet_t MLibRingBufferPush( MLibRingBuffer_t *pHandle,
                                     const void       *pData,
                                     MLibErr_t        *pErr     );
/* リングバッファ追加(上書き許可) */
extern MLibRet_t MLibRingBufferPushOW( MLibRingBuffer_t *pHandle,
                                       const void       *pData,
                                       MLibErr_t        *pErr     );


/******************************************************************************/
/* インライン関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       リングバッファデータ数取得
 * @details     リングバッファに追加されているデータ数を取得する。
 *
 * @param[in]   *pHandle リングバッファハンドル
 *
 * @return      データ数を返す。
 */
/******************************************************************************/
static inline size_t MLibRingBufferGetNum( MLibRingBuffer_t *pHandle )
{
    /* パラメータ判定 */
    if ( pHandle == NULL ) {
        /* 不正 */

        return 0;
    }

    /* データ数返却 */
    return pHandle->num;
}


/******************************************************************************/
#endif
