#ifndef __DYNAMIC_JNIDEMO_H__
#define __DYNAMIC_JNIDEMO_H__

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

int registerNatives(JNIEnv* env);

jstring testDynamicRegister(JNIEnv* env, jobject obj);

#ifdef __cplusplus
}
#endif
#endif // __DYNAMIC_JNIDEMO_H__
