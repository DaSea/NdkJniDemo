/*
 * Copyright (C) 2016-08-12 Dasea <dhf0214@126.com>
 *
 * Description: 动态注册方法的实现
 */
#include "dynamic_jnidemo.h"
#include "log.h"

#include <cstdio>

/**
* 方法对应表
*/
static JNINativeMethod gMethods[] = {
    {"testDynamicRegister", "()Ljava/lang/String;", (void*)testDynamicRegister},//绑定
};

// 注册方法
static int registerNativeMethods(JNIEnv* env, const char* className,
		JNINativeMethod* gMethods, int numMethods);

/*
* 为某一个类注册本地方法
*/
int registerNativeMethods(JNIEnv* env, const char* className,
		JNINativeMethod* gMethods, int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        LOGD_D("不能找到类: %s", className);
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}


/*
* 为所有类注册本地方法
*/
int registerNatives(JNIEnv* env) {
    const char* kClassName = "com/dasea/ndkjnidemo/JniDemo";//指定要注册的类
    return registerNativeMethods(env, kClassName, gMethods,
            sizeof(gMethods) / sizeof(gMethods[0]));
}

// native 方法
jstring testDynamicRegister(JNIEnv* env, jobject obj)
{
	LOGD_D("JAVA 调用这个方法了, 并且c++端会返回一个响应!");
    return env->NewStringUTF("动态注册JNI");
}
