/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibWrapper.h                                             */
/*                                                                 2020/12/31 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_WRAPPER_H_
#define _MLIB_WRAPPER_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/** ラッパー関数テーブル */
typedef struct {
    void *( *pMemcpy )( void       *pDst,
                        const void *pSrc,
                        size_t     size    );   /**< memcpy */
    void *( *pMemset )( void       *pAddr,
                        int        value,
                        size_t     size    );   /**< memset */
    void *( *pMalloc )( size_t     size    );   /**< malloc */
    void  ( *pFree   )( void       *pAddr  );   /**< free   */
} MLibWrapperFunc_t;


/******************************************************************************/
/* ライブラリ関数宣言                                                         */
/******************************************************************************/
/* Wrapper初期化 */
extern void MLibWrapperInit( MLibWrapperFunc_t func );
/* free */
extern void MLibWrapperFree( void *pAddr );
/* malloc */
extern void *MLibWrapperMalloc( size_t size );
/* memcpy */
extern void *MLibWrapperMemcpy( void       *pDst,
                                const void *pSrc,
                                size_t     size   );
/* memset */
extern void *MLibWrapperMemset( void   *pAddr,
                                int    value,
                                size_t size    );


/******************************************************************************/
#endif
