//
// Created by 花歹 on 2018/8/31.
//

#ifndef STRUCTUREANDALGORITHMS_ARRAYQUEUE_H
#define STRUCTUREANDALGORITHMS_ARRAYQUEUE_H

#include <malloc.h>

template<class E>
class ArrayQueue {
private:
    //size 2的幂次
    int size = 0;

    int head = 0;

    int tail = 0;

    //数组地址
    E *array;

public:

    ArrayQueue();

    ArrayQueue(int size);

    ~ArrayQueue();

    bool isEmpty();

    E pop();


    E peek();

    //推入队列中 添加到队尾
    void push(E e);

    void growArray();

    void copyElement(E *array, int tail, E *new_array, int i, int r);
};


template<class E>
ArrayQueue<E>::ArrayQueue(int size) {
    //保证是2 的幂次
    int init_size = size;
    if (init_size >= 4) {
        init_size |= init_size >> 1;
        init_size |= init_size >> 2;
        init_size |= init_size >> 4;
        init_size |= init_size >> 8;
        init_size |= init_size >> 16;

        //int 4 字节  32位
        init_size += 1;
    }

    this->size = init_size;
    array = (E *) malloc(sizeof(E) * size);


}

template<class E>
void ArrayQueue<E>::push(E e) {
    head = (head - 1) & (size - 1); //-1  保证添加进来后 head往前挪动，并且为-1的时候，自动挪到队尾。
    array[head] = e;
    if (tail == head) {
        //扩容
        growArray();
    }

}

template<class E>
E ArrayQueue<E>::pop() {
    tail = (tail - 1) & (size - 1); //   保证添加进来后 head往前挪动，并且为-1的时候，自动挪到队尾。
    return array[tail];
}


template<class E>
bool ArrayQueue<E>::isEmpty() {
    return tail == head;
}

template<class E>
ArrayQueue<E>::~ArrayQueue() {
    free(array);
}

template<class E>
void ArrayQueue<E>::growArray() {
    //
    int new_size = size << 1; // 扩容为2倍，

    E *new_array = (E *)malloc(sizeof(E) * new_size);

    //扩容后 数组乱了，需要重新调整数组中的数据
    int r = size - tail;
    copyElement(array, tail, new_array, 0, r);
    copyElement(array, 0, new_array, r, tail);

    free(array);
    head = 0;
    tail = size;
    size = new_size;
    array = new_array;
    //将tail前面的拷贝到后面



}

template<class E>
void ArrayQueue::copyElement(E *src, int sPo, E *dest, int dPo, int len) {

    for (int i = 0; i < len; ++i) {
        dest[dPo + i] = src[sPo + i];

    }
}

#endif //STRUCTUREANDALGORITHMS_ARRAYQUEUE_H
