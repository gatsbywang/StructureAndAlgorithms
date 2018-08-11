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
    E value;

public:
    Node(E value, Node<E> *next) {
        this->value = value;
        this->next = next;
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
    void push(E e);

    Node<E> *node(int index);

    int size();

    E get(int index);

    void insert(int index, E e);

    void remove(int index);

    ~LinkedList();
};

template<class E>
void LinkedList<E>::push(E e) {
    Node<E> *new_node = new Node<E>(e, NULL);

    if (head) {
        //找到尾巴节点，再添加
        /* Node<E> *h = head;
         while (h){
             if(h->next == NULL){
                 break;
             }
             h = h->next;
         }
         h->next = new_node;*/

        //记录last节点
//        Node<E> *last = node(len - 1);
        last->next = new_node;//O(1)
    } else {
        head = new_node;
    }
    last = new_node;
    len++;
}

template<class E>
Node<E> *LinkedList<E>::node(int index) {   //O(n)
    Node<E> *h = head;
    for (int i = 0; i < index; i++) {
        h = h->next;
    }
    return h;
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

    Node<E> *new_node = new Node<E>(e, NULL);
    if (index == 0) {
        Node<E> *h = head;
        head = new_node;

        new_node->next = h;
    } else {


        Node<E> *new_node = new Node<E>(e, NULL);

        Node<E> *prev = node(index - 1);

        Node<E> *temp = prev->next;
        prev->next = new_node;
        new_node->next = temp;
    }
    len++;
}

template<class E>
void LinkedList<E>::remove(int index) {
    //边界问题
    assert(index >= 0 && index < len);
    if (index == 0) {
        Node<E> *h = head;

        head = h->next;

        delete h;
    } else {
        Node<E> *prev = node(index - 1);
        Node<E> *cur = prev->next;

        prev->next = cur->next;

        delete cur;

    }
    len--;
}

template<class E>
LinkedList<E>::~LinkedList() {
}

#endif //STRUCTUREANDALGORITHMS_LINKEDLIST_HPP

