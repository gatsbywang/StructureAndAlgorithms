//
// Created by 花歹 on 2018/10/21.
//
#include <iostream>
#include <android/log.h>

using namespace std;
#ifndef STRUCTUREANDALGORITHMS_PRIORITY_H
#define STRUCTUREANDALGORITHMS_PRIORITY_H

template<class E>
class PriorityQueue {
    int count; //数组的大小，不够要扩容
    int index = 0; //当前数据的角标的位置(以1开始)
    E *array = NULL;

private:
    void shiftUp(int index) {
        if (index > 1 && array[index] > array[index / 2]) {
            swap(array[index], array[index / 2]);

            shiftUp(index / 2);
        }
    }

    //往下调整为大根堆
    void shiftDown(int k) {
        while (k * 2 <= index) { //到底的情况
            //最大指向左孩子
            int max = 2 * k;
            //有右孩子，且右孩子大于左孩子
            if (max + 1 <= index && array[max + 1] > array[max]) {
                max = max + 1;
            }

            //最大的是自己
            if (array[k] > array[max]) {
                break;
            }

            //交换，
            swap(array[k],array[max]);
            k = max;
        }
    }

public:
    PriorityQueue(int count) {
        this->count = count;
        array = new E[count];
    }

    bool isEmpty() {
        return index == 0;
    }


    E pop() {
        E max = array[1];

        array[1] = array[index];
        index--;

        shiftDown(1);

        return max;
    }

    void push(E e) {
        array[index + 1] = e;

        index++;

        //不断的调整堆
        shiftUp(index);


        for (int i = 0; i < index; ++i) {
            __android_log_print(ANDROID_LOG_ERROR, "TAG", "%d", array[i + 1]);
        }
    }
};


#endif //STRUCTUREANDALGORITHMS_PRIORITY_H
