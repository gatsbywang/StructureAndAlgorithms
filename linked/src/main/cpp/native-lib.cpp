#include <jni.h>
#include <string>
#include <android/log.h>
#include "LinkedList.hpp"

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    LinkedList<int> linkedList;


    clock_t  start =clock();
    for(int i=0;i<50000;i++){
        linkedList.push(i);
    }
    clock_t  end =clock();
    __android_log_print(ANDROID_LOG_ERROR, "TAG", "%d", (end-start)/CLOCKS_PER_SEC);


    linkedList.push(1);
    linkedList.push(2);

    linkedList.insert(0, -1);
    linkedList.insert(linkedList.size(), 3);
    linkedList.insert(2, 22);

    linkedList.remove(0);
    linkedList.remove(linkedList.size() - 1);

    for (int i = 0; i < linkedList.size(); i++) {
        __android_log_print(ANDROID_LOG_ERROR, "TAG", "%d", linkedList.get(i));
    }


    return env->NewStringUTF(hello.c_str());
}
