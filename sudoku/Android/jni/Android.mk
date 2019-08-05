LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SUDOKU_PROJECT_PATH := $(LOCAL_PATH)/../../..

LOCAL_MODULE := sudoku
LOCAL_MODULE_FILENAME := libsudoku

LOCAL_C_INCLUDES := $(SUDOKU_PROJECT_PATH)/include
LOCAL_C_INCLUDES += $(SUDOKU_PROJECT_PATH)/sudoku/include

LOCAL_CFLAGS := -std=c11

LOCAL_SRC_FILES := $(shell bash $(LOCAL_PATH)/ListSRC.sh ${SUDOKU_PROJECT_PATH})

# LOCAL_CPPFLAGS := -std=c++11 # for cpp
# TARGET_FORMAT_STRING_CFLAGS := -Wformat # -Werror=format-security

# compiled inside flag: -Wl,--whole-archive -Wl,--no-whole-archive
# LOCAL_WHOLE_STATIC_LIBRARIES := libxxx # use with other library
# outside whole archive flag
# LOCAL_STATIC_LIBRARIES :=
# LOCAL_SHARED_LIBRARIES :=

include $(BUILD_SHARED_LIBRARY)

# search for lib Android.mk in environment NDK_MODULE_PATH (path separate with ':')
# $(call import-module,libxxx) 
