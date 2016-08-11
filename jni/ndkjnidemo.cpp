#include "ndkjnidemo.h"
#include <cstring>

#ifndef NULL
#define NULL (0)
#endif

// 测试参数
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicData(
        JNIEnv* env, jobject obj, jboolean jb, jint ji, jdouble jd, jstring js){
    union 
        unsigned int a;
        unsigned char b;
    }c;
    c.a = 1;
    if (1 == c.b) {
        LOGD_D("小端序");
    } else {
        LOGD_D("大端序");
    }

    unsigned short u2dec = 0x1122;
    char buffer[3] = {0};
    memcpy(buffer, &u2dec, 2);
    LOGD_D("Buffer: %x; %x", (int)buffer[0], (int)buffer[1]);
    unsigned int dec = static_cast<unsigned int>(ji);
    LOGD_D("u4: %x", dec);

    LOGD_D("BasicData: boolean: %d; int:%d, double: %f",
            jb, (int)ji, (double)jd);

    LOGD_D("=====================testBasicData begin==========================");
    // String UTF-8
    jboolean isCopy = JNI_FALSE;
    const char* strCh = (const char*)env->GetStringUTFChars(js, &isCopy);
    int strSize = env->GetStringUTFLength(js);
    LOGD_D("String: %s, size is: %d", strCh, strSize);
    env->ReleaseStringUTFChars(js, strCh);

    // String unicode
    const unsigned short* strU2 = env->GetStringChars(js, &isCopy);
    int u2size = env->GetStringLength(js);
    LOGD_D("String: %s, size is: %d", (char*)strU2, u2size);
    LOGD_D("=====================testBasicData end==========================");
}

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectData(
        JNIEnv* env, jobject obj, jobject jobjData) {
    LOGD_D("=====================testObjectData begin==========================");
    jclass jJniData = env->FindClass("com/dasea/ndkjnidemo/JniData");
    if(NULL == jJniData) {
        LOGD_D("Not find class!");
        return ;
    }

    jfieldID jbData = env->GetFieldID(jJniData, "bData", "Z");
    jfieldID jdData = env->GetFieldID(jJniData, "dData", "D");
    jfieldID jiData = env->GetFieldID(jJniData, "iData", "I");
    jfieldID jcData = env->GetFieldID(jJniData, "cData", "B");
    jfieldID jsData = env->GetFieldID(jJniData, "sData", "Ljava/lang/String;");
    jfieldID jbyteArr = env->GetFieldID(jJniData, "byteArr", "[B");
    jfieldID jintArr = env->GetFieldID(jJniData, "intArr", "[I");

    // 基本数据类型
    unsigned char bData = (unsigned char)env->GetBooleanField(jobjData, jbData);
    double dData = (double)env->GetDoubleField(jobjData, jdData);
    int iData = (int)env->GetIntField(jobjData, jiData);
    char cData = (char)env->GetByteField(jobjData, jcData);
    LOGD_D("基本数据: %d, d:  %f, i: %d, c: %d", bData, dData, iData, cData);

    // string类型
    jboolean isCopy = JNI_FALSE;
    jstring sData = (jstring)env->GetObjectField(jobjData, jsData);
    const char* strCh = (const char*)env->GetStringUTFChars(sData, &isCopy);
    int strSize = (int)env->GetStringLength(sData);
    LOGD_D("String : %s, size: %d", strCh, strSize);
    env->ReleaseStringUTFChars(sData, strCh);

    // 测试数组
    jbyteArray byteArr = (jbyteArray)env->GetObjectField(jobjData, jbyteArr);
    // 方法1: 将本地的数组指针直接指向java端的数组地址, 依赖于jvm实现, 对引用的数据增加引用计数
    // 速度和效率比GetByteArrayRegion高, 需要使用ReleaseByteArrayElements释放,否则会有内存泄露
    signed char* bytes = env->GetByteArrayElements(byteArr, &isCopy);
    int arrSize = env->GetArrayLength(byteArr);
    for (int i = 0; i < arrSize; ++i) {
        /* code */
        LOGD_D("Index->value: %d->%d", i, bytes[i]);
    }
    env->ReleaseByteArrayElements(byteArr, bytes, 0);

    // 方法2: 将java端数组的数据拷贝 到 本地数组中
    jintArray intArr = (jintArray)env->GetObjectField(jobjData, jintArr);
    int intArrSize = env->GetArrayLength(intArr);
    int* arrBuf = new int[intArrSize];
    env->GetIntArrayRegion(intArr, 0, intArrSize, arrBuf);
    for (int i = 0; i < intArrSize; ++i) {
        LOGD_D("Index->value: %d -> %d", i, arrBuf[i]);
    }
    delete[] arrBuf;
    arrBuf = NULL;

    // 测试int数组, 类似于byte数组, env->GetIntArrayElements()
    LOGD_D("=====================testObjectData end==========================");
}

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicArrData(
        JNIEnv* env, jobject obj, jintArray jarrData) {
    LOGD_D("=====================testBasicArrData begin==========================");
    jboolean isCopy = JNI_FALSE;
    int* bytes = env->GetIntArrayElements(jarrData, &isCopy);
    int arrSize = env->GetArrayLength(jarrData);
    for (int i = 0;i < arrSize; ++i) {
        /* code */
        LOGD_D("Index->value: %d->%d", i, bytes[i]);
    }
    env->ReleaseIntArrayElements(jarrData, bytes, 0);
    LOGD_D("=====================testBasicArrData end==========================");
}

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStringArrData(
        JNIEnv* env, jobject obj, jobjectArray jarrData) {
    LOGD_D("=====================testStringArrData begin==========================");
    jstring jstrData = NULL;
    int size = env->GetArrayLength(jarrData);

    const char* strCh = NULL;
    jboolean isCopy = JNI_FALSE;
    for(int i = 0; i < size; ++i) {
        jstrData = (jstring)env->GetObjectArrayElement(jarrData, i);
        strCh = (const char*)env->GetStringUTFChars(jstrData, &isCopy);
        LOGD_D("Index-> string: %d - %s", i, strCh);
        env->ReleaseStringUTFChars(jstrData, strCh);

        strCh = NULL;
    }
    LOGD_D("=====================testStringArrData end==========================");
}

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectArrData(
        JNIEnv* env, jobject obj, jobjectArray jarrData) {
    LOGD_D("=====================testObjectArrData begin==========================");
    // 类
    jclass jJniData = env->FindClass("com/dasea/ndkjnidemo/JniData");
    if(NULL == jJniData) {
        LOGD_D("Not find class!");
        return ;
    }

    jfieldID jbData = env->GetFieldID(jJniData, "bData", "Z");
    jfieldID jdData = env->GetFieldID(jJniData, "dData", "D");
    jfieldID jiData = env->GetFieldID(jJniData, "iData", "I");
    jfieldID jcData = env->GetFieldID(jJniData, "cData", "B");
    jfieldID jsData = env->GetFieldID(jJniData, "sData", "Ljava/lang/String;");
    jfieldID jbyteArr = env->GetFieldID(jJniData, "byteArr", "[B");
    jfieldID jintArr = env->GetFieldID(jJniData, "intArr", "[I");

    int size = env->GetArrayLength(jarrData);
    LOGD_D("Object 数组长度: %d", size);
    jboolean isCopy = JNI_FALSE;
    jobject jobjData;
    for(int i = 0; i < size; ++i) {
        jobjData = env->GetObjectArrayElement(jarrData, i);

        // 获取object里面的数据
        int iData = env->GetIntField(jobjData, jiData);
        double dData = env->GetDoubleField(jobjData, jdData);

        // 其他成员的测试和testObjectData里面的一样
        // string类型
        jstring sData = (jstring)env->GetObjectField(jobjData, jsData);
        const char* strCh = (const char*)env->GetStringUTFChars(sData, &isCopy);
        int strSize = (int)env->GetStringLength(sData);
        LOGD_D("Index(%d): %d, %f, String : %s", i, iData, dData, strCh);
        env->ReleaseStringUTFChars(sData, strCh);
    }
    LOGD_D("=====================testObjectArrData end==========================");
}

// 测试返回值
JNIEXPORT jint JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicDataRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testBasicDataRet begin==========================");
    LOGD_D("=====================testBasicDataRet end==========================");
    return (28);
}

JNIEXPORT jstring JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStringDataRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testStringDataRet begin==========================");
    jstring jstr = env->NewStringUTF("这是从c++端返回的string测试数据!");
    // env->DeleteLocalRef(jstr); // 是否需要? 待考察, 关于local reference的问题
    // 对于local reference, 在native方法返回的时候会自动释放(freed)
    // 但是对于在创建大量local reference的native方法里面, 最好及时释放
    // native memory(local reference) -> java heap(java object)
    LOGD_D("=====================testStringDataRet end==========================");
    return (jstr);
}

JNIEXPORT jobject JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjectDataRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testObjDataRet end==========================");
    // 类
    jclass jJniData = env->FindClass("com/dasea/ndkjnidemo/JniData");
    if(NULL == jJniData) {
        LOGD_D("Not find class!");
        return NULL;
    }

    // 构造函数
    jmethodID initID = env->GetMethodID(jJniData, "<init>", "()V");
    jobject jresult = env->NewObject(jJniData, initID);
    if (NULL == jresult || env->ExceptionOccurred()) {
        LOGD_D("Construct object failed!");
        return  NULL;
    }

    jfieldID jbData = env->GetFieldID(jJniData, "bData", "Z");
    jfieldID jdData = env->GetFieldID(jJniData, "dData", "D");
    jfieldID jiData = env->GetFieldID(jJniData, "iData", "I");
    jfieldID jcData = env->GetFieldID(jJniData, "cData", "B");
    jfieldID jsData = env->GetFieldID(jJniData, "sData", "Ljava/lang/String;");
    jfieldID jbyteArr = env->GetFieldID(jJniData, "byteArr", "[B");
    jfieldID jintArr = env->GetFieldID(jJniData, "intArr", "[I");


    // 设置基本类型的内容
    env->SetBooleanField(jresult, jbData, 0);
    env->SetDoubleField(jresult, jdData, 30.240182372);
    env->SetIntField(jresult, jiData, 4457);
    env->SetByteField(jresult, jcData, 87);

    // 设置String
    jstring strData = env->NewStringUTF("这是c++设置的字符串!");
    env->SetObjectField(jresult, jsData, strData);
    env->DeleteLocalRef(strData);

    // 设置数组类型
    char cArr[11] = {23, 24, 25, 26, 27, 28, 29, 43, 55, 66, 0};
    int  iArr[11] = {123, 124, 345, 664, 553, 222, 445, 167, 876, 548};
    jbyteArray byteArr = (jbyteArray)env->GetObjectField(jresult, jbyteArr);
    jintArray intArr = (jintArray)env->GetObjectField(jresult, jintArr);
    env->SetByteArrayRegion(byteArr, 0, 10, (const signed char*)cArr);
    env->SetIntArrayRegion(intArr, 0, 10, iArr);

    LOGD_D("=====================testObjDataRet end==========================");
    return (jresult);
}

JNIEXPORT jintArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testBasicDataArrRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testBasicDataArrRet end==========================");
    jintArray jintArr = env->NewIntArray(10);
    int  iArr[11] = {123, 124, 345, 664, 553, 222, 445, 167, 876, 548};
    env->SetIntArrayRegion(jintArr, 0, 10, iArr);
    LOGD_D("=====================testBasicDataArrRet end==========================");
    return (jintArr);
}

JNIEXPORT jobjectArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStrDataArrRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testStrDataArrRet begin 11==========================");
    jstring jstrObj = env->NewStringUTF("测试string数组返回的 -> 1");
    jobjectArray jstrArr = env->NewObjectArray(3, env->GetObjectClass(jstrObj), jstrObj);
    // 1, 快速修改
    jstring jstrObj1 = env->NewStringUTF("测试string数组返回的 -> 2");
    jstring jstrObj2 = env->NewStringUTF("测试string数组返回的 -> 3");
    env->SetObjectArrayElement(jstrArr, 1, jstrObj1);
    env->SetObjectArrayElement(jstrArr, 2, jstrObj2);

    // 2, 其他修改方式
    LOGD_D("=====================testStrDataArrRet end==========================");
    return jstrArr;
}

JNIEXPORT jobjectArray JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjDataArrRet(
        JNIEnv* env, jobject obj) {
    LOGD_D("=====================testObjDataArrRet begin==========================");
    // 类
    jclass jJniData = env->FindClass("com/dasea/ndkjnidemo/JniData");
    if(NULL == jJniData) {
        LOGD_D("Not find class!");
        return NULL;
    }

    // 构造函数
    jmethodID initID = env->GetMethodID(jJniData, "<init>", "()V");
    jobject jresult = env->NewObject(jJniData, initID);
    if (NULL == jresult || env->ExceptionOccurred()) {
        LOGD_D("Construct object failed!");
        return  NULL;
    }

    jfieldID jbData = env->GetFieldID(jJniData, "bData", "Z");
    jfieldID jdData = env->GetFieldID(jJniData, "dData", "D");
    jfieldID jiData = env->GetFieldID(jJniData, "iData", "I");
    jfieldID jcData = env->GetFieldID(jJniData, "cData", "B");
    jfieldID jsData = env->GetFieldID(jJniData, "sData", "Ljava/lang/String;");
    jfieldID jbyteArr = env->GetFieldID(jJniData, "byteArr", "[B");
    jfieldID jintArr = env->GetFieldID(jJniData, "intArr", "[I");


    // 设置基本类型的内容
    env->SetBooleanField(jresult, jbData, 0);
    env->SetDoubleField(jresult, jdData, 30.240182372);
    env->SetIntField(jresult, jiData, 4457);
    env->SetByteField(jresult, jcData, 87);

    // 设置String
    jstring strData = env->NewStringUTF("这是c++设置的字符串!");
    env->SetObjectField(jresult, jsData, strData);
    env->DeleteLocalRef(strData);

    // 设置数组类型
    char cArr[11] = {23, 24, 25, 26, 27, 28, 29, 43, 55, 66, 0};
    int  iArr[11] = {123, 124, 345, 664, 553, 222, 445, 167, 876, 548};
    jbyteArray byteArr = (jbyteArray)env->GetObjectField(jresult, jbyteArr);
    jintArray intArr = (jintArray)env->GetObjectField(jresult, jintArr);
    env->SetByteArrayRegion(byteArr, 0, 10, (const signed char*)cArr);
    env->SetIntArrayRegion(intArr, 0, 10, iArr);

    jobjectArray jobjArr = env->NewObjectArray(3, jJniData, jresult);
    // 自己可以获取每个元素, 再详细设置其值

    LOGD_D("=====================testObjDataArrRet end==========================");
    return jobjArr;
}

// 测试用参数返回数据
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testStrDataRetByParam(
        JNIEnv* env, jobject obj, jstring jstrRet) {
    LOGD_D("=====================testStrDataRetByParam end==========================");
    jboolean isCopy = JNI_FALSE;
    char* str = const_cast<char*>(env->GetStringUTFChars(jstrRet, &isCopy));
    int len = env->GetStringUTFLength(jstrRet);

    // 能不能改写呢(下列方案失败)
    const char* testStr = "hello!";
    memcpy(str, testStr, 5);
    env->ReleaseStringUTFChars(jstrRet, str);

    LOGD_D("=====================testStrDataRetByParam end==========================");
}
JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testObjDataRetByParam(
        JNIEnv* env, jobject obj, jobject jobjRet) {
    LOGD_D("=====================testObjDataRetByParam end==========================");
    // 类
    jclass jJniData = env->FindClass("com/dasea/ndkjnidemo/JniData");
    if(NULL == jJniData) {
        LOGD_D("Not find class!");
        return ;
    }

    jfieldID jbData = env->GetFieldID(jJniData, "bData", "Z");
    jfieldID jdData = env->GetFieldID(jJniData, "dData", "D");
    jfieldID jiData = env->GetFieldID(jJniData, "iData", "I");
    jfieldID jcData = env->GetFieldID(jJniData, "cData", "B");
    jfieldID jsData = env->GetFieldID(jJniData, "sData", "Ljava/lang/String;");
    jfieldID jbyteArr = env->GetFieldID(jJniData, "byteArr", "[B");
    jfieldID jintArr = env->GetFieldID(jJniData, "intArr", "[I");

    // 设置基本类型的内容
    env->SetBooleanField(jobjRet, jbData, 0);
    env->SetDoubleField(jobjRet, jdData, 30.240182372);
    env->SetIntField(jobjRet, jiData, 4457);
    env->SetByteField(jobjRet, jcData, 87);

    // 设置String
    jstring strData = env->NewStringUTF("这是c++设置的字符串!");
    env->SetObjectField(jobjRet, jsData, strData);
    env->DeleteLocalRef(strData);

    // 设置数组类型
    char cArr[11] = {23, 24, 25, 26, 27, 28, 29, 43, 55, 66, 0};
    int  iArr[11] = {123, 124, 345, 664, 553, 222, 445, 167, 876, 548};
    jbyteArray byteArr = (jbyteArray)env->GetObjectField(jobjRet, jbyteArr);
    jintArray intArr = (jintArray)env->GetObjectField(jobjRet, jintArr);
    env->SetByteArrayRegion(byteArr, 0, 10, (const signed char*)cArr);
    env->SetIntArrayRegion(intArr, 0, 10, iArr);

    LOGD_D("=====================testObjDataRetByParam end==========================");
}

JNIEXPORT void JNICALL Java_com_dasea_ndkjnidemo_JniDemo_testArrDataRetByParam(
        JNIEnv* env, jobject obj, jintArray jarrData, jint jarrLen) {
    LOGD_D("=====================testArrDataRetByParam end==========================");
    int len = jarrLen;

    jboolean isCopy = JNI_FALSE;
    jint* intele = env->GetIntArrayElements(jarrData, &isCopy);
    // 数据
    for (int i = 0; i < len; ++i) {
        LOGD_D("%d : %d", i, intele[i]);
    }
    env->ReleaseIntArrayElements(jarrData, intele, 0);

    int* iArr = new int[len];
    if (NULL == iArr) {
        return ;
    }

    for (int i = 0; i < len; ++i) {
        iArr[i] = i*10 + 25;
    }

    env->SetIntArrayRegion(jarrData, 0, len, iArr);
    LOGD_D("=====================testArrDataRetByParam end==========================");
}
