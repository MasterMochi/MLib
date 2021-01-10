/******************************************************************************/
/*                                                                            */
/* src/include/MLib/MLibUtil.h                                                */
/*                                                                 2021/01/04 */
/* Copyright (C) 2020-2021 Mochi.                                             */
/*                                                                            */
/******************************************************************************/
#ifndef _MLIB_UTIL_H_
#define _MLIB_UTIL_H_
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdint.h>


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/** アライメント計算マクロ */
#define MLIB_UTIL_ALIGN( _VALUE, _ALIGNMENT ) \
    ( ( ( _VALUE ) + ( ( _ALIGNMENT ) - 1 ) ) & ~( ( _ALIGNMENT ) - 1 ) )

/** フラグ判定マクロ */
#define MLIB_UTIL_HAVE_FLAG( _VALUE, _FLAG ) \
    ( ( ( _VALUE ) & ( _FLAG ) ) == ( _FLAG ) )

/** MAX関数マクロ */
#define MLIB_UTIL_MAX( _VALUE1, _VALUE2 ) \
    ( ( _VALUE1 ) > ( _VALUE2 ) ? ( _VALUE1 ) : ( _VALUE2 ) )
/** MIN関数マクロ */
#define MLIB_UTIL_MIN( _VALUE1, _VALUE2 ) \
    ( ( _VALUE1 ) < ( _VALUE2 ) ? ( _VALUE1 ) : ( _VALUE2 ) )

/** 配列エントリ数計算マクロ */
#define MLIB_UTIL_NUMOF( _ARRAY ) \
    ( sizeof ( _ARRAY ) / sizeof ( _ARRAY[ 0 ] ) )

/** アドレスサイズ加算マクロ */
#define MLIB_UTIL_ADDR_ADD_SIZE( _PADDR, _SIZE ) \
    ( ( void * ) ( ( size_t ) ( _PADDR ) + ( _SIZE ) ) )


/******************************************************************************/
/* ライブラリ関数宣言                                                         */
/******************************************************************************/
/* 文字列比較 */
extern int MLibUtilCmpString( const char *pStr1,
                              const char *pStr2,
                              size_t     length  );
/* メモリコピー */
extern void MLibUtilCopyMemory( void       *pDst,
                                const void *pSrc,
                                size_t     size   );

/* メモリコピー(memcpy互換) */
extern void *MLibUtilCopyMemoryCmpt( void       *pDst,
                                     const void *pSrc,
                                     size_t     size   );

/* メモリ設定(8bit毎) */
extern void MLibUtilSetMemory8( void    *pAddr,
                                uint8_t value,
                                size_t  size    );

/* メモリ設定(16bit毎) */
extern void MLibUtilSetMemory16( void     *pAddr,
                                 uint16_t value,
                                 size_t   size    );

/* メモリ設定(32bit毎) */
extern void MLibUtilSetMemory32( void     *pAddr,
                                 uint32_t value,
                                 size_t   size    );

/* メモリ設定(memset互換) */
extern void *MLibUtilSetMemoryCmpt( void   *pAddr,
                                    int    value,
                                    size_t size    );


/******************************************************************************/
#endif
