//
// Created by 花歹 on 2018/8/28.
//


//用数组实现   (java stack源码)
#ifndef H
#define H

#include <malloc.h>

template<class E>
class ArrayStack {
private:
    //栈顶元素的角标位置
    int top = -1;
    E *array = NULL;
    //初始的长度
    int size = 10;
public:
    ArrayStack();

    ~ArrayStack();

public:
    /**
     * 栈是否为空
     * @return
     */
    bool isEmpty();

    /**
     * 弹出栈顶的元素
     * @return
     */
    E pop();

    /**
     * 获取栈顶的元素但不弹出
     * @return
     */
    E peek();

    /**
     * 将元素入栈
     */
    void push(E e);

private:
    void growArray();
};

template<class E>
ArrayStack<E>::ArrayStack() {
    array = (E *)malloc(sizeof(E) * size);
}


ArrayStack::~ArrayStack() {
    delete[] array;
}

template<class E>
E ArrayStack<E>::pop() {
    return array[top--];
}

template<class E>
bool ArrayStack<E>::isEmpty() {
    return top == -1;
}

template<class E>
E ArrayStack::peek() {
    return array[top];
}


template<class E>
void ArrayStack<E>::push(E e) {
    //是否有足够的空间
    if (top + 1 == size) {
        //扩容
        growArray();
    }

    array[++top] = e;
}

template<class E>
void ArrayStack<E>::growArray() {
    //
    size += size >> 1;
    array = (E *)realloc(array,size* sizeof(E));//重新开辟，为啥用传array,这样返回的还是array的首地址
}

#endif //H