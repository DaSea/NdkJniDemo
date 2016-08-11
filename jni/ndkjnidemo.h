/*
 * ndkjnidemo.h
 *
 *  Created on: 2016-5-1
 *      Author: DaSea
 */

#ifndef NDKJNIDEMO_H_
#define NDKJNIDEMO_H_

#include <jni.h>
#include "log.h"

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicData(
        JNIEnv* env, jobject obj, jboolean jb, jint ji, jdouble jd, jstring js);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectData(
        JNIEnv* env, jobject obj, jobject jobjData);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicArrData(
        JNIEnv* env, jobject obj, jintArray jarrData);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStringArrData(
        JNIEnv* env, jobject obj, jobjectArray jarrData);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectArrData(
        JNIEnv* env, jobject obj, jobjectArray jarrData);

JNIEXPORT jint JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicDataRet(
        JNIEnv* env, jobject obj);
JNIEXPORT jstring JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStringDataRet(
        JNIEnv* env, jobject obj);
JNIEXPORT jobject JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectDataRet(
        JNIEnv* env, jobject obj);

JNIEXPORT jintArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicDataArrRet(
        JNIEnv* env, jobject obj);
JNIEXPORT jobjectArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStrDataArrRet(
        JNIEnv* env, jobject obj);
JNIEXPORT jobjectArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjDataArrRet(
        JNIEnv* env, jobject obj);

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStrDataRetByParam(
        JNIEnv* env, jobject obj, jstring jstrRet);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjDataRetByParam(
        JNIEnv* env, jobject obj, jobject jobjRet);
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testArrDataRetByParam(
        JNIEnv* env, jobject obj, jintArray jarrData, jint jarrLen);

#ifdef __cplusplus
}
#endif

#endif /* NDKJNIDEMO_H_ */
