#include <jni.h>
#include <android/log.h>
#include <string>

#define TAG "TAG"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);


void hannuota(int n, char start, char help, char end) {
    if (n == 1) {
        //直接从
        LOGE("把 %d个盘子从 %c挪动到 %c", n, start, end);
    } else {
        //
        hannuota(n - 1, start, end, help);
        LOGE("把 %d个盘子从 %c挪动到 %c", n, start, end);
        hannuota(n - 1, help, start, end);
    }

}


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {


    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}
