#******************************************************************************#
#*                                                                            *#
#* src/Makefile                                                               *#
#*                                                                 2020/07/19 *#
#* Copyright (C) 2018-2020 Mochi.                                             *#
#*                                                                            *#
#******************************************************************************#
#******************************************************************************#
#* 設定                                                                       *#
#******************************************************************************#
# ライブラリ
LIB = libMLib

# ソースコード
SRCS  = DynamicArray/DynamicArrayAlloc.c
SRCS += DynamicArray/DynamicArrayChunk.c
SRCS += DynamicArray/DynamicArrayExit.c
SRCS += DynamicArray/DynamicArrayForeach.c
SRCS += DynamicArray/DynamicArrayFree.c
SRCS += DynamicArray/DynamicArrayGet.c
SRCS += DynamicArray/DynamicArrayInit.c
SRCS += DynamicArray/DynamicArraySearch.c
SRCS += List/ListGet.c
SRCS += List/ListInit.c
SRCS += List/ListInsert.c
SRCS += List/ListRemove.c
SRCS += List/ListSearch.c
SRCS += RingBuffer/RingBufferClear.c
SRCS += RingBuffer/RingBufferExit.c
SRCS += RingBuffer/RingBufferInit.c
SRCS += RingBuffer/RingBufferPop.c
SRCS += RingBuffer/RingBufferPush.c
SRCS += Spin/SpinInit.c
SRCS += Spin/SpinLock.c
SRCS += Spin/SpinUnlock.c
SRCS += Split/SplitGet.c
SRCS += Split/SplitInit.c
SRCS += Split/SplitTerm.c
SRCS += State/StateInit.c
SRCS += State/StateExec.c
SRCS += State/StateGet.c
SRCS += State/StateSet.c

# ビルドディレクトリ
BUILD_DIR   = ../build
# リリースディレクトリ
RELEASE_DIR = $(BUILD_DIR)/release
# オブジェクトディレクトリ
OBJ_DIR     = $(BUILD_DIR)/obj

# Cフラグ
CFLAGS  = -O
CFLAGS += -Wall
CFLAGS += -masm=intel
CFLAGS += -m32
CFLAGS += -fno-pic
CFLAGS += -ffreestanding
CFLAGS += -Iinclude
CFLAGS += -I$(RELEASE_DIR)/include
CFLAGS += -I$(BUILD_DIR)/include


#******************************************************************************#
#* 定義                                                                       *#
#******************************************************************************#
# オブジェクトサブディレクトリ
OBJ_SUBDIRS = $(sort $(addprefix $(OBJ_DIR)/, $(dir $(SRCS))))

# オブジェクトファイル
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# 依存関係ファイル
DEPS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.d))


#******************************************************************************#
#* phonyターゲット                                                            *#
#******************************************************************************#
.PHONY: all
all: $(OBJ_SUBDIRS) $(RELEASE_DIR)/$(LIB).a Makefile

.PHONY: clean
clean:
	-rm -rf $(RELEASE_DIR)/$(LIB).a
	-rm -rf $(OBJ_DIR)

#******************************************************************************#
#* 生成規則                                                                   *#
#******************************************************************************#
# 依存関係
-include $(DEPS)

# オブジェクトサブディレクトリ
ifdef OBJ_SUBDIRS
$(OBJ_SUBDIRS):
	mkdir -p $@
endif

# ライブラリ
$(RELEASE_DIR)/$(LIB).a: $(OBJS) Makefile
	$(AR) rcs $(OBJ_DIR)/$(LIB).a $(OBJS)
	ln -srf $(OBJ_DIR)/$(LIB).a $@

# アセンブラファイルコンパイル
$(OBJ_DIR)/%.o: %.s Makefile
	$(AS) -o $@ $<

# Cファイルコンパイル
$(OBJ_DIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -MD -MP


#******************************************************************************#
