
#ifndef __ANDROID_JNI_HELPER_H__
#define __ANDROID_JNI_HELPER_H__

#include <jni.h>
#include <string>
#include <map>
using namespace std;

typedef struct JniMethodInfo_
{
    JNIEnv *    env;
    jobject     object;
    jclass      classID;
    jmethodID   methodID;
} JniMethodInfo;


class JniHelper
{
public:
    static void setJavaVM(JavaVM *javaVM);
    static JavaVM* getJavaVM();
    static JNIEnv* getEnv();

    static bool setClassLoaderFrom(jobject activityInstance);
    static bool getStaticMethodInfo(JniMethodInfo &methodinfo,
                                    const char *className,
                                    const char *methodName,
                                    const char *paramCode);
    static bool getMethodInfo(JniMethodInfo &methodinfo,
                              const char *className,
                              const char *methodName,
                              const char *paramCode);

    static std::string jstring2string(jstring str);

    static void setJniClassObject(const char *className,jobject obj);
    static jobject getJniClassObject(const char *className);

    static jmethodID loadclassMethod_methodID;
    static jobject classloader;

    //类实例（对象）底层是无法获取的，需将jni传进来的保存
    static map<string,jobject> m_aJniClassObjects;

private:
    static JNIEnv* cacheEnv(JavaVM* jvm);

    static bool getMethodInfo_DefaultClassLoader(JniMethodInfo &methodinfo,
                                                 const char *className,
                                                 const char *methodName,
                                                 const char *paramCode);

    static JavaVM* _psJavaVM;
};

#endif // __ANDROID_JNI_HELPER_H__
