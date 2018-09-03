//
// Created by 花歹 on 2018/8/28.
//


//用数组实现   (java stack源码)
#ifndef H
#define H

#include <malloc.h>
#include <assert.h>

template<class E>
class Node {
public:
    Node *next;

    E value;

public:
    Node(E value, Node<E> *next) {
        this->value = value;
        this->next = next;
    }

    ~Node(){

    }
};

template<class E>
class LinkStack {
private:
    //头结点
    Node<E> *head = NULL;

    int index = 0;

    Node<E> *top = NULL; //栈顶节点


public:
    LinkStack();

    ~LinkStack();

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

    Node<E> *node(int index);
};

template<class E>
void LinkStack<E>::push(E e) {
    Node<E> *new_node = new Node<E>(e, NULL);
    if (top) {
        top->next = new_node;
    } else {
        head = new_node;
    }
    top = new_node;
    index++;
}

// 弹
template<class E>
E LinkStack<E>::pop() {

    assert(index >= 0);
    delete top;

    //将top指向前一个 o(n)复杂度 ,利用双链表解决寻找算法的O(n)
    top = node(index - 1);
}

template<class E>
Node<E> *LinkStack<E>::node(int index) {

    Node<E> *h = head;
    for (int i = 0; i < index; i++) {
        h = h->next;
    }
    return h;
}

template<class E>
LinkStack<E>::~LinkStack() {
    Node<E> *h = head;

    while (head) {
        Node *next = h->next;
        delete h;
        head = next;
    }
    head = NULL;
}

#endif //H