//
// Created by 花歹 on 2018/8/11.
//



#ifndef STRUCTUREANDALGORITHMS_LINKEDLIST_HPP
#define STRUCTUREANDALGORITHMS_LINKEDLIST_HPP

#include <iostream>
#include <cassert>

using namespace std;

//单链表
template<class E>
struct Node {
    Node<E> *next;
    Node<E> *prev;
    E value;

public:
    Node(E value, Node<E> *prev, Node<E> *next) {
        this->value = value;
        this->next = next;
        this->prev = prev;
    }
};

template<class E>
class LinkedList {
    //头指针
    Node<E> *head = NULL;

    //代表集合的长度
    int len = 0;

    //尾指针
    Node<E> *last = NULL;


public:
    /**
    * 添加数据
    * @param e 元素
    */
    void push(E e);

    int size();

    E get(int index);

    // remove insert
    void insert(int index, E e);

    E remove(int index);

    ~LinkedList();

    Node<E> *node(int i);

    void linkLast(E e);

    void linkBefore(Node<E> *pNode, E e);

    E unlink(Node<E> *pNode);
};

template<class E>
void LinkedList<E>::push(E e) {
    // 添加一个数据
    linkLast(e);
    /*Node<E> *new_node = new Node<E>(e, NULL);

    if (head) {// 0 -> 1 -> 2 -> 3
        // ?
        // head->next = new_node;
        // 找到尾巴节点，有一个特定就是 next 节点为空
        *//*Node<E>* h = head;
        while(h){
            if(h->next == NULL){
                break;
            }
            h = h->next;
        }
        h->next = new_node;*//*
        // 每一次都需要找到最后一个节点  50000
        // 记录 last 节点

        // Node<E> *last = node(len - 1);
        last->next = new_node;// O(1)
    } else {
        head = new_node;
    }
    last = new_node;*/

    len++;
}

template<class E>
Node<E> *LinkedList<E>::node(int index) {   //O(n)
    if(index < len >> 1){
        // 从前往后变量
        Node<E> *cur = head;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur;
    }
    else{
        // 从后往前遍历
        Node<E> *cur = last;
        for (int i = len - 1; i > index; i--) {
            cur = cur->prev;
        }
        return cur;
    }
}

template<class E>
int LinkedList<E>::size() {
    return len;
}

template<class E>
E LinkedList<E>::get(int index) {

    //越界判断
    assert(index >= 0 && index < len);
    return node(index)->value;
}

template<class E>
void LinkedList<E>::insert(int index, E e) {

    assert(index >= 0 && index <= len);
    // 考虑边界  0
    if (index == len) {
        linkLast(e);
    } else {
        linkBefore(node(index), e);
    }

    /*Node<E> *new_node = new Node<E>(e, NULL);
    if (index == 0) {
        Node<E> *h = head;
        head = new_node;
        new_node->next = h;
    } else {
        // 考虑最后一个位置
        Node<E> *prev = node(index - 1);
        Node<E> *next = prev->next;// NULL
        prev->next = new_node;
        new_node->next = next;
    }*/

    len++;
}

template<class E>
E LinkedList<E>::remove(int index) {
    //边界问题
    // 考虑边界问题  0  ， len , mid
    assert(index >= 0 && index < len);

    return unlink(node(index));
//    if (index == 0) {
//        Node<E> *h = head;
//
//        head = h->next;
//
//        delete h;
//    } else {
//        Node<E> *prev = node(index - 1);
//        Node<E> *cur = prev->next;
//
//        prev->next = cur->next;
//
//        delete cur;
//
//    }
//    len--;
}

template<class E>
LinkedList<E>::~LinkedList() {

    //释放内存？析构节点指针
    Node<E> *h = head;
    while(h){
        Node<E> *next = h->next;
        delete h;
        h = next;
    }

    //头指针 以及尾指针 要置空
    head = NULL;
    last = NULL;

}

template<class E>
void LinkedList<E>::linkLast(E e) {
    Node<E> *l = last;
    Node<E> *new_node = new Node<E>(e, l, NULL);
    last = new_node;

    if (head) {
        l->next = new_node;
    } else {
        head = new_node;
    }
}

template<class E>
void LinkedList<E>::linkBefore(Node<E> *cur, E e) {
    Node<E> *prev = cur->prev;// NULL
    Node<E> *new_node = new Node<E>(e, prev, cur);
    // 当前的上一个节点 = 新增的节点
    cur->prev = new_node;
    // 上一个节点的 next -> 新增的节点  , 0 特殊处理
    if (prev) {
        prev->next = new_node;
    } else {// 0
        head = new_node;
    }
}

template<class E>
E LinkedList<E>::unlink(Node<E> *cur) {
    // 左右两个节点
    Node<E> *prev = cur->prev;
    Node<E> *next = cur->next;

    E value = cur->value;

    // 有两个为空的情况， 严谨 ，思维灵活
    if(prev){
        prev->next = next;
    } else {
        head = next;
    }

    if(next){
        next->prev = prev;
    } else {
        last = prev;
    }

    delete cur;
    len--;
    return value;
}

#endif //STRUCTUREANDALGORITHMS_LINKEDLIST_HPP

