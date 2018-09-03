//
// Created by 花歹 on 2018/8/16.
//

#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <android/log.h>

#define TAG "TAG"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);


namespace ArrayUtil {


    int *create_random_array(int len, int low, int high) {
        int *arr = new int[len];

        for (int i = 0; i < len; ++i) {
            arr[i] = rand() % (high - low) + low;
        }

        return arr;
    }
//
    int *copy_random_array(int *arr, int len) {
        int *copy_arr = new int[len];
        memcpy(copy_arr, arr, sizeof(int) * len);
        return copy_arr;
    }
//
    void sort_array(char *sortName, void(*sort)(int *, int), int *arr, int len) {

        size_t start_time = clock();

        sort(arr, len);
        size_t end_time = clock();

        //计算算法执行时间
        double time = (double) (end_time - start_time) / CLOCKS_PER_SEC;

        LOGE("%s的执行时间；%lf", sortName, time);
        for (int i = 0; i < len - 1; ++i) {
            assert(arr[i] < arr[i + 1]);
        }

    }
}