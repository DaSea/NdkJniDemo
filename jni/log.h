#ifndef __DEBUG_LOG_H__
#define __DEBUG_LOG_H__

#include <android/log.h>
#define TAG "JniDemo"

#define LOGD_D(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGD_E(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGD_I(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

#endif
