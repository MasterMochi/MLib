#******************************************************************************#
#*                                                                            *#
#* src/Makefile                                                               *#
#*                                                                 2020/12/31 *#
#* Copyright (C) 2018-2020 Mochi.                                             *#
#*                                                                            *#
#******************************************************************************#
#******************************************************************************#
#* 設定                                                                       *#
#******************************************************************************#
# ライブラリ
LIB    = libMLib
# ライブラリ(フリースタンディング環境版)
LIB_FE = libMLib_fe

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
SRCS += Util/UtilCmpString.c
SRCS += Util/UtilCopyMemory.c
SRCS += Util/UtilSetMemory.c
SRCS += Wrapper/WrapperFree.c
SRCS += Wrapper/WrapperInit.c
SRCS += Wrapper/WrapperMalloc.c
SRCS += Wrapper/WrapperMemcpy.c
SRCS += Wrapper/WrapperMemset.c

# ビルドディレクトリ
BUILD_DIR   = ../build
# リリースディレクトリ
RELEASE_DIR = $(BUILD_DIR)/release
# オブジェクトディレクトリ
OBJ_DIR     = $(BUILD_DIR)/obj
# オブジェクトディレクトリ(フリースタンディング環境版)
OBJ_DIR_FE  = $(BUILD_DIR)/obj_fe

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
OBJ_SUBDIRS    = $(sort $(addprefix $(OBJ_DIR)/,    $(dir $(SRCS))))
OBJ_SUBDIRS_FE = $(sort $(addprefix $(OBJ_DIR_FE)/, $(dir $(SRCS))))

# オブジェクトファイル
OBJS    = $(addprefix $(OBJ_DIR)/,    $(SRCS:.c=.o))
OBJS_FE = $(addprefix $(OBJ_DIR_FE)/, $(SRCS:.c=.o))

# 依存関係ファイル
DEPS    = $(addprefix $(OBJ_DIR)/,    $(SRCS:.c=.d))
DEPS_FE = $(addprefix $(OBJ_DIR_FE)/, $(SRCS:.c=.d))


#******************************************************************************#
#* phonyターゲット                                                            *#
#******************************************************************************#
.PHONY: all
all: $(OBJ_SUBDIRS) $(OBJ_SUBDIRS_FE) $(RELEASE_DIR)/$(LIB).a $(RELEASE_DIR)/$(LIB_FE).a Makefile

.PHONY: clean
clean:
	-rm -rf $(RELEASE_DIR)/$(LIB).a
	-rm -rf $(RELEASE_DIR)/$(LIB_FE).a
	-rm -rf $(OBJ_DIR)
	-rm -rf $(OBJ_DIR_FE)


#******************************************************************************#
#* 生成規則                                                                   *#
#******************************************************************************#
# 依存関係
-include $(DEPS)
-include $(DEPS_FE)

# オブジェクトサブディレクトリ
ifdef OBJ_SUBDIRS
$(OBJ_SUBDIRS):
	mkdir -p $@
endif
ifdef OBJ_SUBDIRS_FE
$(OBJ_SUBDIRS_FE):
	mkdir -p $@
endif

# ライブラリ
$(RELEASE_DIR)/$(LIB).a: $(OBJS) Makefile
	$(AR) rcs $(OBJ_DIR)/$(LIB).a $(OBJS)
	ln -srf $(OBJ_DIR)/$(LIB).a $@

# ライブラリ(フリースタンディング環境版)
$(RELEASE_DIR)/$(LIB_FE).a: $(OBJS_FE) Makefile
	$(AR) rcs $(OBJ_DIR_FE)/$(LIB_FE).a $(OBJS_FE)
	ln -srf $(OBJ_DIR_FE)/$(LIB_FE).a $@

# アセンブラファイルコンパイル
$(OBJ_DIR)/%.o: %.s Makefile
	$(AS) -o $@ $<
$(OBJ_DIR_FE)/%.o: %.s Makefile
	$(AS) -o $@ $<

# Cファイルコンパイル
$(OBJ_DIR)/%.o: %.c Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -MD -MP
$(OBJ_DIR_FE)/%.o: %.c Makefile
	$(CC) $(CFLAGS) -DMLIB_FE -o $@ -c $< -MD -MP


#******************************************************************************#
