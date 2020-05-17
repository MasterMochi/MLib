/******************************************************************************/
/*                                                                            */
/* test/DynamicArray/main.c                                                   */
/*                                                                 2020/05/13 */
/* Copyright (C) 2020 Mochi.                                                  */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/* インクルード                                                               */
/******************************************************************************/
/* 標準ヘッダ */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/******************************************************************************/
/* グローバル関数宣言                                                         */
/******************************************************************************/
/*------*/
/* Init */
/*------*/
extern bool InitSuccess1( void );
extern bool InitSuccess2( void );
extern bool InitFailure1( void );
extern bool InitFailure2( void );
extern bool InitFailure3( void );
extern bool InitFailure4( void );

/*-------*/
/* Alloc */
/*-------*/
extern bool AllocSuccess1( void );


/******************************************************************************/
/* 定義                                                                       */
/******************************************************************************/
/** テスト関数型 */
typedef bool ( *TestFunc_t )( void );
/** テスト関数表エントリ */
typedef struct {
    char       *pTestName;  /**< テスト名   */
    TestFunc_t pTestFunc;   /**< テスト関数 */
} TestEntry_t;


/******************************************************************************/
/* 静的グローバル変数定義                                                     */
/******************************************************************************/
/** テスト関数表 */
static const TestEntry_t gTestTbl[] =
    {
        /*------+------------------------------------+----------------*/
        /* IDX  | テスト名                           | テスト関数     */
        /*------+------------------------------------+----------------*/
        /* 0 */ { "MLibDynamicArrayInit() :Success:1", &InitSuccess1  },
        /* 1 */ { "MLibDynamicArrayInit() :Success:2", &InitSuccess2  },
        /* 2 */ { "MLibDynamicArrayInit() :Failure:1", &InitFailure1  },
        /* 3 */ { "MLibDynamicArrayInit() :Failure:2", &InitFailure2  },
        /* 4 */ { "MLibDynamicArrayInit() :Failure:3", &InitFailure3  },
        /* 5 */ { "MLibDynamicArrayInit() :Failure:4", &InitFailure4  },
        /* 6 */ { "MLibDynamicArrayAlloc():Success:1", &AllocSuccess1 },
        /* 6 */ { NULL                               , NULL           },
    };


/******************************************************************************/
/* グローバル関数定義                                                         */
/******************************************************************************/
/******************************************************************************/
/**
 * @brief       動的配列テストエントリ関数
 * @details     MLibライブラリの動的配列をテストする。
 *
 * @param[in]   argNum  引数数
 * @param[in]   *pArg[] 引数
 *
 * @return      テスト結果を返す。
 * @retval      EXIT_SUCCESS 成功
 * @retval      EXIT_FAILURE 失敗
 */
/******************************************************************************/
int main( int  argNum,
          char *pArg[] )
{
    int  idx;       /* テストインデックス */
    int  ret;       /* 戻り値             */
    bool result;    /* テスト結果         */

    /* 初期化 */
    idx    = 0;
    ret    = EXIT_FAILURE;
    result = false;

    /* テストタイトル表示 */
    printf( " MLib/DynamicArray:\n" );
    printf( "--------------------\n" );

    /* テスト毎に繰り返す */
    while ( gTestTbl[ idx ].pTestFunc != NULL ) {
        /* テスト開始表示 */
        printf( "    (%3d)[ %s ]...", idx + 1, gTestTbl[ idx ].pTestName );

        /* テスト実行 */
        result = ( gTestTbl[ idx ].pTestFunc )();

        /* テスト結果判定 */
        if ( result == false ) {
            /* 失敗 */

            ret = EXIT_FAILURE;

        } else {
            /* 成功 */

            /* 結果表示 */
            printf( "OK.\n" );
        }

        /* 次テストへ */
        idx++;
    }

    return ret;
}


/******************************************************************************/

