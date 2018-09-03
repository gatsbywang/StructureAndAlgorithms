#include <jni.h>
#include <string>
#include "LinkStack.hpp"

#define TAG "TAG"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    //栈内存 方法也是栈内存，回去调用方法中new的对象的析构方法
//    LinkStack<int> stack;
    //需要通过new LinkStack  才不会把push方法里的new对象析构
    LinkStack<int> *stack = new LinkStack<int>();
    stack->push(1);


    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}
