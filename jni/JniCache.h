/*
 * jnicache.h
 *  存放使用过程中缓存的类，字段ID及方法ID
 */

#ifndef _JNI_CHACHE_H_
#define _JNI_CHACHE_H_

#include <jni.h>

struct JNativeMgr {
    jclass _jnativeMgr;

    jmethodID _jtestvoidfunc;
    jmethodID _jtestC2JByBasicData;
    jmethodID _jtestC2JByArrData;
    jmethodID _jtestC2JByStrData;
    jmethodID _jtestC2JByStrArr;
    jmethodID _jtestC2JByObjData;
    jmethodID _jtestC2JByObjArr;
};

struct JniTestData {
    jclass _jJniData;

    jfieldID _jbdata;
    jfieldID _jdData;
    jfieldID _jiData;
    jfieldID _jcData;
    jfieldID _jsData;
    jfieldID _jbyteArr;
    jfieldID _jintArr;
};



#endif

