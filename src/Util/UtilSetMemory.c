/******************************************************************************/
/*                                                                            */
/* src/Util/UtilSetMemory.c                                                   */
/*                                                                 2020/12/31 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stddef.h>
#include <stdint.h>

/* ライブラリヘッダ */
#include <MLib/MLibUtil.h>


/******************************************************************************/
/* ライブラリ関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       メモリ設定(8bit毎)
 * @details     pAddrを先頭に8bit毎にvalueの値をsize分設定する。
 *
 * @param[in]   *pAddr 設定先アドレス
 * @param[in]   value  設定値
 * @param[in]   size   設定サイズ
 */
/******************************************************************************/
void MLibUtilSetMemory8( void    *pAddr,
                         uint8_t value,
                         size_t  size    )
{
    size_t offset;

    /* 1byte毎に繰り返す */
    for ( offset = 0; offset < size; offset++ ) {
        *( ( ( uint8_t * ) pAddr ) + offset ) = value;
    }

    return;
}


/******************************************************************************/
/**
 * @brief       メモリ設定(16bit毎)
 * @details     pAddrを先頭に16bit毎にvalueの値をsize分設定する。
 *
 * @param[in]   *pAddr 設定先アドレス
 * @param[in]   value  設定値
 * @param[in]   size   設定サイズ
 */
/******************************************************************************/
void MLibUtilSetMemory16( void     *pAddr,
                          uint16_t value,
                          size_t   size    )
{
    size_t offset;
    size_t offset_max;

    /* 初期化 */
    offset_max = size / 2;

    /* 2byte毎に繰り返す */
    for ( offset = 0; offset < offset_max; offset++ ) {
        *( ( ( uint16_t * ) pAddr ) + offset ) = value;
    }

    /* 1byte毎に繰り返す */
    for ( offset *= 2; offset < size; offset++ ) {
        *( ( ( uint8_t * ) pAddr  ) + offset ) =
        *( ( ( uint8_t * ) &value ) + ( offset % 2 ) );
    }

    return;
}


/******************************************************************************/
/**
 * @brief       メモリ設定(32bit毎)
 * @details     pAddrを先頭に32bit毎にvalueの値をsize分設定する。
 *
 * @param[in]   *pAddr 設定先アドレス
 * @param[in]   value  設定値
 * @param[in]   size   設定サイズ
 */
/******************************************************************************/
void MLibUtilSetMemory32( void     *pAddr,
                          uint32_t value,
                          size_t   size    )
{
    size_t offset;
    size_t offset_max;

    /* 初期化 */
    offset_max = size / 4;

    /* 4byte毎に繰り返す */
    for ( offset = 0; offset < offset_max; offset++ ) {
        *( ( ( uint16_t * ) pAddr ) + offset ) = value;
    }

    /* 1byte毎に繰り返す */
    for ( offset *= 4; offset < size; offset++ ) {
        *( ( ( uint8_t * ) pAddr  ) + offset ) =
        *( ( ( uint8_t * ) &value ) + ( offset % 3 ) );
    }

    return;
}


/******************************************************************************/
/**
 * @brief       メモリ設定(memset互換)
 * @details     引数pAddrを先頭に1byte毎に引数valueの値を引数size分設定する。
 *
 * @param[in]   *pAddr 設定先アドレス
 * @param[in]   value  設定値
 * @param[in]   size   設定サイズ
 *
 * @return      設定先アドレスを返す。
 *
 * @note        引数valueはint型であるが、char型にキャストし使用する。
 */
/******************************************************************************/
void *MLibUtilSetMemoryCmpt( void   *pAddr,
                             int    value,
                             size_t size    )
{
    MLibUtilSetMemory8( pAddr, ( uint8_t ) value, size );

    return pAddr;
}


/******************************************************************************/
