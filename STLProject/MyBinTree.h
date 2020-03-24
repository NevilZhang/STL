#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<class type> struct Tree_node {
    type value;//节点的数据
    Tree_node* parent;//父节点指针
    Tree_node* left_Child;//左孩子指针
    Tree_node* right_Child;//右孩子指针
    unsigned int height;//树高

    Tree_node() {
        height = -1;
    }
    Tree_node(type data) :value(data), parent(NULL), left_Child(NULL), right_Child(NULL) {
        height = 0;
    }
    ~Tree_node() {
        parent = NULL;
        left_Child = NULL;
        right_Child = NULL;
        height = 0;
    }
};

//二叉树模板
template<class type>
class BinTree
{
protected:
    Tree_node<type>* root;
public:
    BinTree();
    ~BinTree();
    virtual void Print() = 0;//打印二叉树
    virtual Tree_node<type>* Search(type data) = 0;//搜索树
    virtual bool Insert(type data) = 0;//插入节点
    virtual bool Delete(type data) = 0;//删除节点
    virtual void UpdateHeight(Tree_node<type> &node);//更新树高度
    //virtual BinTree<type>* Merge(BinTree* other_tree) = 0;
    void Bintree2Array(Tree_node<type>* tree, vector<type>& array);
    void Array2Bintree(vector<type>& array, int l, int r, Tree_node<type>* tree);
};

template<class type>
inline BinTree<type>::BinTree()
{
    this->root = nullptr;
}

template<class type>
inline BinTree<type>::~BinTree()
{
    /*
     * 二叉树析构需要释放每一个节点的内存空间
     */
    Tree_node<type>* p = this->root;
    stack<Tree_node<type>*> t_stack;
    if (p != nullptr) {
        t_stack.push(p);
        while (!t_stack.empty()) {
            p = t_stack.top();
            t_stack.pop();
            if (p->left_Child != nullptr) {
                t_stack.push(p->left_Child);
            }
            if(p->right_Child != nullptr) {
                t_stack.push(p->right_Child);
            }
            delete p;
        }
    }
    this->root = nullptr;
}

template<class type>
inline void BinTree<type>::UpdateHeight(Tree_node<type>& node)
{
    if (&node != nullptr) {
        Tree_node<type>* p = &node;
        while (p != nullptr) {
            if (p->left_Child == nullptr && p->right_Child != nullptr) {
                p->height = p->right_Child->height + 1;
            }
            else if(p->left_Child != nullptr && p->right_Child == nullptr){
                p->height = p->left_Child->height + 1;
            }
            else if (p->left_Child != nullptr && p->right_Child != nullptr) {
                p->height = p->left_Child->height > p->right_Child->height ? 
                    p->left_Child->height + 1 : p->right_Child->height + 1;
            }
            else {
                p->height = 1;
            }
            p = p->parent;
        }
    }
}



template<class type>
inline void BinTree<type>::Bintree2Array(Tree_node<type>* tree, vector<type>& array)
{
    if(tree->left_Child) Bintree2Array(tree->left_Child, array);
    array.push_back(tree->value);
    if (tree->right_Child) Bintree2Array(tree->right_Child, array);
}

template<class type>
inline void BinTree<type>::Array2Bintree(vector<type>& array, int l, int r, Tree_node<type>* tree)
{
    int mid = (l + r) / 2;
    tree->value = array[mid];
    if (mid - l >= 1) {
        Tree_node<type>* tmp = new Tree_node<type>();
        tmp->parent = tree;
        tree->left_Child = tmp;
        Array2Bintree(array, l, mid - 1, tmp);
    }
    else {
        tree->left_Child = nullptr;
    }
    if (r - mid >= 1) {
        Tree_node<type>* tmp = new Tree_node<type>();
        tmp->parent = tree;
        tree->right_Child = tmp;
        Array2Bintree(array, mid + 1, r, tmp);
    }
    else {
        tree->right_Child = nullptr;
    }
}

