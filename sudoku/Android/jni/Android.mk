LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

SUDOKU_PROJECT_PATH := ../../..

LOCAL_MODULE := sudoku
LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SUDOKU_PROJECT_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SUDOKU_PROJECT_PATH)/sudoku/include
LOCAL_CFLAGS := -std=c11

# sudoku
SUDOKU_LIB_PATH := $(LOCAL_PATH)/$(SUDOKU_PROJECT_PATH)/sudoku
SUDOKU_LIB_SRC := ${SUDOKU_LIB_PATH}/src
LOCAL_SRC_FILES :=

include $(BUILD_SHARED_LIBRARY)
