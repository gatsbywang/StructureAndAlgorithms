#include <jni.h>
#include <string>
#include <android/log.h>
#include <stdlib.h>
#include <queue>
#include <cmath>

#define TAG "TAG"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__);


template<class T>
class TreeNode {
public:
    TreeNode(T data) {
        this->data = data;
    }

    T data;
    TreeNode *left;     //左孩子
    TreeNode *right;    //右孩子
};


void preOrderTraverse(TreeNode<char> *pNode, void visit(char));

void visitNode(char data);

int getDepthTree(TreeNode<char> *pNode);

bool isBalanceTree(TreeNode<char> *pNode);

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_demo_StructureAndAlgorithms_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    TreeNode<char> *A = new TreeNode<char>('A');
    TreeNode<char> *B = new TreeNode<char>('B');
    TreeNode<char> *C = new TreeNode<char>('C');
    TreeNode<char> *D = new TreeNode<char>('D');
    TreeNode<char> *E = new TreeNode<char>('E');
    TreeNode<char> *F = new TreeNode<char>('F');

    A->left = B;
    A->right = C;

    B->left = D;
    B->right = E;

    C->right = F;

    // 遍历 （前序，中序，后序，层序）
    preOrderTraverse(A, visitNode);

    int depth = getDepthTree(A);

    bool isBalance = isBalanceTree(A);

    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());
}

bool isBalanceTree(TreeNode<char> *pNode) {
    if (pNode == NULL) {
        return true;
    }
    int leftDapth = getDepthTree(pNode->left);
    int rightDapth = getDepthTree(pNode->right);


    return abs(leftDapth - rightDapth) <= 1 && isBalanceTree(pNode->left) && isBalanceTree(pNode->right);
}

int getDepthTree(TreeNode<char> *pNode) {
    if (pNode == NULL) {
        return 0;
    }

    int leftDapth = getDepthTree(pNode->left);
    int rightDapth = getDepthTree(pNode->right);

    return std::max(leftDapth, rightDapth) + 1 ;
}

/**
 * 前序遍历 (必须写成模板才会通用)(方法的回调)返回值void*visit(T)
 * 思考：排序的稳定性？
 * @param pNode
 */
template<class T>
void preOrderTraverse(TreeNode<T> *pNode, void visit(T)) {
    if (pNode == NULL) {
        return;
    }

    visit(pNode->data);


    //访问左节点
    preOrderTraverse(pNode->left, visit);

    //访问右节点
    preOrderTraverse(pNode->right, visit);

}


void visitNode(char data) {
    LOGE(data + "");
}

/**
 * 中序遍历
 * @tparam T
 * @param pNode
 * @param visit
 */
template<class T>
void infixOrderTraverse(TreeNode<T> *pNode, void visit(T)) {
    if (pNode == NULL) {
        return;
    }

    //访问左节点
    infixOrderTraverse(pNode->left, visit);

    //返回 根节点
    visit(pNode->data);


    //访问右节点
    infixOrderTraverse(pNode->right, visit);

}

/**
 * 后序遍历
 * @tparam T
 * @param pNode
 * @param visit
 */
template<class T>
void epilogueOrderTraverse(TreeNode<T> *pNode, void visit(T)) {
    if (pNode == NULL) {
        return;
    }

    //访问左节点
    epilogueOrderTraverse(pNode->left, visit);

    //访问右节点
    epilogueOrderTraverse(pNode->right, visit);

    //返回 根节点
    visit(pNode->data);

}

/**
 * 层序遍历
 * @tparam T
 * @param pNode
 * @param visit
 */
template<class T>
void levelOrderTraverse(TreeNode<T> *pNode, void visit(T)) {
    if (pNode == NULL) {
        return;
    }

    std::queue<T> nodeQ;

    nodeQ.push(pNode);

    while (!nodeQ.empty()) {
        TreeNode<T> *front = nodeQ.front();
        nodeQ.pop();
        visit(front->data);

        if (front->left) {
            nodeQ.push(front->left);
        }

        if (front->right) {
            nodeQ.push(front->right);
        }
    }

}