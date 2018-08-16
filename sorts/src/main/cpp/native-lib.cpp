#include <jni.h>
#include <string>
#include <android/log.h>
#include "ArrayUtil.cpp"

#define TAG "TAG"
//结构体取别名
//#define int size_t
//typedef int size_t;

//#define printT(int number) print(TAG,int number)

//方法进行更名
void print(char *tag ,int number){

}

//LOGE(...)参数->__android_log_print
//对__android_log_print取别名
// ...可变参数 要换成__VA_ARGS__
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);



/**
 * 冒泡排序：相邻两个数进行比较，如果前面比后面的大，就进行交换。
 * @param arr
 * @param len
 */
void bubbleSort(int arr[],int len){//O(n^2)
    for (int i = 0; i <len-1; ++i) {// n-1
        for(int j=0;j<len-i-1;++j){ //n-1...1
            if(arr[j] > arr[j+1]){
                //一次交换，三次赋值
                std::swap(arr[j],arr[j+1]);
            }
        }
    }
}

/**
 * 遍历出最小的位置，最后与第一个位置进行交换
 * 空间复杂度是O（1）
 * @param arr
 * @param len
 */
void selectSort(int arr[],int len){
    for (int i = 0; i <len; ++i) {
        int min = i;
        for (int j = i+1; j < len; ++j) {
            if(arr[min] > arr[j]){
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
    }

}

void print_array(int arr[], int len){
    for (int i = 0; i < len; ++i) {
//        __android_log_print(ANDROID_LOG_ERROR,TAG,"#d",arr[i]);
        LOGE("%d",arr[i]);
    }
}


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {



    //测试性能，冒泡比选择慢，原因在于交换位置的时候比选择排序多几步。
    int len =10000;
    int *arr = ArrayUtil::create_random_array(len,20,100);
    ArrayUtil::sort_array("bubbleSort", bubbleSort, arr, len);

    delete (arr);

    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}
