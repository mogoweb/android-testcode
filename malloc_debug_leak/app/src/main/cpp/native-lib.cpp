#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_china_1liantong_memoryleaktest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    char* p = (char*)malloc(1024 * 1024);
    if (p) {
        strcpy(p, "hello");
    }
    return env->NewStringUTF(hello.c_str());
}
