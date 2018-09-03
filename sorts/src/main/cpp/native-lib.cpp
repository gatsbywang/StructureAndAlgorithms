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
//void print(char *tag ,int number){
//
//}

//LOGE(...)参数->__android_log_print
//对__android_log_print取别名
// ...可变参数 要换成__VA_ARGS__
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);


/**
 * 冒泡排序：相邻两个数进行比较，如果前面比后面的大，就进行交换。
 * @param arr
 * @param len
 */
void bubbleSort(int arr[], int len) {//O(n^2)
    for (int i = 0; i < len - 1; ++i) {// n-1
        for (int j = 0; j < len - i - 1; ++j) { //n-1...1
            if (arr[j] > arr[j + 1]) {
                //一次交换，三次赋值
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void optimizeBubbleSort(int arr[], int len) {
    //需要记录上一次最后遍历的位置
    int n = len;
    int newn = 0;//控制位置
    do {
        newn = 0;
        for (int i = 1; i < n; ++i) {//
            if (arr[i - 1] > arr[i]) {
                std::swap(arr[i - 1], arr[i]);
                newn = i;//记录最后一次交换的位置
            }
        }
        n = newn;
    } while (n > 0);
}


/**
 * 遍历出最小的位置，最后与第一个位置进行交换
 * 空间复杂度是O（1）
 * @param arr
 * @param len
 */
void selectSort(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
        int min = i;
        for (int j = i + 1; j < len; ++j) {
            if (arr[min] > arr[j]) {
                min = j;
            }
        }
        std::swap(arr[i], arr[min]);
    }

}

//插入排序,向前相邻两个数比较，小的放前面，大的放后面。
void insertSort(int arr[], int len) {

    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (arr[j] < arr[j - 1]) {
                std::swap(arr[j], arr[j - 1]);
            } else {
                break;
            }

        }
    }
}

void optimizeInsertSort(int arr[], int len) {
    int j;
    for (int i = 1; i < len; ++i) {
        int temp = arr[i];
        for (j = i; j > 0; --j) {
            if (arr[j - 1] > temp) {
                arr[j] = arr[j - 1];
            } else {
                break;
            }
        }

        arr[j] = temp;
    }
}

//希尔排序，对插入排序分组()
//接近于有序的数列，插入排序要比希尔排序要快。
void shellInsertSort(int arr[], int len) {
    //
    int increament = len / 2;//2组数据

    int i, j, k;
    while (increament > 0) {

        for (i = 0; i < increament; ++i) {
            //
            for (j = i + increament; j < len; j += increament) {
                int temp = arr[j];
                for (k = j; k > i && arr[k - increament] > temp; k -= increament) {
                    arr[k] = arr[k - increament];
                }
                arr[k + increament] = temp;
            }
        }

        increament /= 2;
    }
}

// 对数组区间 [l,mid] 和 [mid+1,r]归并
void merge_(int arr[], int l, int mid, int r) {
    // 1、对数组进行一次拷贝
    int temp[r - l + 1];
    for (int i = l; i <= r; ++i) {
        temp[i - l] = arr[i];
    }

    //2、确定好分析之后的变量
    int i = l;
    int j = mid + 1;
    int k = l;

    for (; k <= r; ++k) {

        if(i>mid){
            arr[k] = temp[j - l];
            j++;
        } else if(j>r){
            arr[k] = temp[i - l];
            i++;
        } else if (temp[i-l] < temp[j-l]) {
            arr[k] = temp[i - l];
            i++;
        } else{
            arr[k] = temp[j - l];
            j++;
        }



    }

}

//对数组的[l,r]区间进行归并排序
void mergeSort_(int arr[], int l, int r) {
    if (l >= r) {
        return;
    }

    int mid = (l + r) >> 1;
    mergeSort_(arr, l, mid);
    mergeSort_(arr, mid + 1, r);
    //优化，只有当前半部分的最后一个数字大于排序后半部分第一个数字的时候才进行归并排序。
    if(arr[mid] >arr[mid+1]){
        merge_(arr, l, mid, r);

    }
}

//归并算法
void mergeSort(int arr[], int len) {
    mergeSort_(arr,0,len-1);
}

//对数组arr区间[l,r] 进行分割排序
int partition(int arr[], int l, int r){

    //优化 跟区间[l,r]随机位置进行比较。
    std::swap(arr[l],arr[rand()%(r-l+1)+l]);
    int v =arr[l];
    //以p为分割，[l+1,p]<v [p+1,r] >v
    int p = l;

    for (int i = l; i <=r ; ++i) {
        if(arr[i]<v){
            //只需要处理小于的情况
            std::swap(arr[p+1],arr[i]);
            p++;
        }
    }

    std::swap(arr[l],arr[p]);
    return  p ;
}

//对数组arr区间[l,r] 进行快速排序
void quickSort_(int arr[], int l, int r) {
    if(l>=r){
        return;
    }

    int p = partition(arr,l,r);
    quickSort_(arr,l,p-1);
    quickSort_(arr,p+1,r);
}


void quickSort(int arr[], int len){
    srand(time(NULL));
    quickSort_(arr, 0, len-1);
}


//对数组arr区间[l,r] 进行快速排序
void quickSort3ways_(int arr[], int l, int r) {
    if(l>=r){
        return;
    }

  //  int p = partition(arr,l,r);

    //定义变量
    std::swap(arr[l],arr[rand()%(r-l+1)+l]);
    int v =arr[l];

    int lt =l;//[l+1,lt] <v
    int gt = r+1;//[gt,r]>r
    int i = l+1;//[lt+1,i)=v

    while(gt >i){
        if(arr[i] > v){

            std::swap(arr[i], arr[gt - 1]);
            gt--;

        }else if(arr[i]<v){
            std::swap(arr[i], arr[lt + 1]);
            i++;
            lt++;
        }else{
            i++;
        }


    }
    //将=的移除 ，只对大于和小于的进行快排
    quickSort3ways_(arr,l,lt-1);
    quickSort3ways_(arr,gt,r);
}

void quickSort3ways(int arr[], int len){

    srand(time(NULL));


}



void print_array(int arr[], int len) {
    for (int i = 0; i < len; ++i) {
//        __android_log_print(ANDROID_LOG_ERROR,TAG,"#d",arr[i]);
        LOGE("%d", arr[i]);
    }
}


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {



    //测试性能，冒泡比选择慢，原因在于交换位置的时候比选择排序多几步。
//    int len =10000;
//    int *arr = ArrayUtil::create_random_array(len,20,100);
//    ArrayUtil::sort_array("bubbleSort", bubbleSort, arr, len);

//    delete (arr);

    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}
