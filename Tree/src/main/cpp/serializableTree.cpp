//
// Created by 花歹 on 2018/9/19.
//

#include <iostream>

#define TREE_SIZE 100

template<class T>
class TreeNode {
public:
    TreeNode(T data) {
        this->data = data;
    }

    T data;
    TreeNode *left = NULL;     //左孩子
    TreeNode *right = NULL;    //右孩子
};


void serializeTree() {

}