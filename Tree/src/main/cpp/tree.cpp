//
// Created by 花歹 on 2018/9/19.
//

#include "tree.h"
#include <iostream>
#define TREE_SIZE 100

typedef char  Element;

typedef struct CTNode{
    int child;//孩子的下标
    struct CTNode *next;

} *CTreePtr;

typedef struct {
    Element data;//存放数据 A B C

    int parent;// 双亲节点的角标

    CTreePtr firstChild; //第一个子孩子的 CTNode*
} CTree;

typedef struct {
    CTree nodes[TREE_SIZE];//存放节点的数组

    int root;//根节点的位置

    int size;//节点的个数


}Tree;

