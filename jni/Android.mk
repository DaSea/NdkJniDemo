LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := ndkjnidemo
LOCAL_SRC_FILES := ndkjnidemo.cpp
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)
