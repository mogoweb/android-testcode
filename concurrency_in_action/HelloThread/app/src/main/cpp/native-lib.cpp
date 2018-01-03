#include <jni.h>
#include <iostream>
#include <string>
#include <thread>

static std::string hello_str = "Hello from C++";

void hello() {
    hello_str = "Hello Concurrent World";
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_china_1liantong_hellothread_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::thread	t(hello);
    t.join();

    return env->NewStringUTF(hello_str.c_str());
}
