#pragma once
#include <iostream>
#include <queue>
#include "MyBinTree.h"
using namespace std;
/*
 * ƽ�������
 */
template<class type>
class AVTree : public BinTree<type>
{
public:
	Tree_node<type>* root;
	AVTree();
	AVTree(Tree_node<type>* node);
	void Print();	//���������е����ݴ�ӡ����
	Tree_node<type>* Search(type data);	//�����ڵ㺯��
	bool Insert(type data);	//����ڵ㺯��
	bool Delete(type data);	//ɾ���ڵ㺯��
	Tree_node<type>* Merge(AVTree* other_tree);//�ϲ�����������
	void PreorderTraverse(Tree_node<type>* node, vector<type>& results);//�������
	void InorderTraverse(Tree_node<type>* node, vector<type>& results);//�������
	void PostorderTraverse(Tree_node<type>* node, vector<type>& results);//�������
	vector<type> BFS();//������ȱ���
	vector<type> DFS();//������ȱ���
private:
	int CalculateBF(Tree_node<type>& node);
	void Rotate(Tree_node<type>& node);
	void Connect34(Tree_node<type>* N, Tree_node<type>* L, Tree_node<type>* R, 
		Tree_node<type>* LL, Tree_node<type>* LR, Tree_node<type>* RL, Tree_node<type>* RR);
};

template<class type>
inline AVTree<type>::AVTree()
{
	this->root = nullptr;
}

template<class type>
inline AVTree<type>::AVTree(Tree_node<type>* node)
{
	this->root = node;
}

template<class type>
inline void AVTree<type>::Print()
{
	queue<Tree_node<type>*>* now_queue = new queue<Tree_node<type>*>;
	Tree_node<type>* ro = this->root;
	now_queue->push(ro);
	queue<Tree_node<type>*>* next_queue = new queue<Tree_node<type>*>;
	while (!next_queue->empty() || !now_queue->empty()) {

		while (!now_queue->empty()) {
			Tree_node<type>* _node = now_queue->front();
			now_queue->pop();
			cout << _node->value << "\t";
			if (_node->left_Child) next_queue->push(_node->left_Child);
			if (_node->right_Child) next_queue->push(_node->right_Child);
		}
		cout << endl;
		now_queue = next_queue;
		next_queue = new queue<Tree_node<type>*>;
	}
}

template<class type>
inline Tree_node<type>* AVTree<type>::Search(type data)
{
	if (this->root == nullptr) {
		return nullptr;//����
	}
	Tree_node<type>* s_node = this->root;
	Tree_node<type>* p_node = s_node->parent;
	while (s_node != nullptr && s_node->value != data) {
		p_node = s_node;
		if (data > s_node->value) {
			s_node = s_node->right_Child;
		}
		else {
			s_node = s_node->left_Child;
		}
	}
	if (s_node == nullptr) {
		return p_node;
	}
	else {
		return s_node;
	}
}

template<class type>
inline bool AVTree<type>::Insert(type data)
{
	Tree_node<type>* pos = Search(data);
	if (pos != nullptr && pos->value == data) {
		return false;//�����Ѵ���
	}
	//����Ҫ����Ľڵ�
	Tree_node<type>* insert_node = new Tree_node<type>(data);
	insert_node->height = 1;
	insert_node->parent = pos;
	if (pos != nullptr) {
		(data > pos->value ? pos->right_Child : pos->left_Child) = insert_node;
	}
	else {
		this->root = insert_node;
	}

	BinTree<type>::UpdateHeight(*insert_node);

	Tree_node<type>* check_node;
	check_node = insert_node->parent;
	
	while (check_node != nullptr && abs(CalculateBF(*check_node)) <= 1) {
		//�����Ƿ���ʧ��ڵ�
		check_node = check_node->parent;
	}
	if (check_node != nullptr) {
		//����ʧ��ڵ��������ת
		Rotate(*check_node);
	}
	return true;
}

template<class type>
inline bool AVTree<type>::Delete(type data)
{
	Tree_node<type>* pos = this->Search(data);
	if (pos == nullptr || pos->value != data) {
		return false;
	}
	Tree_node<type>* replacingNode;//�滻�ڵ�
	Tree_node<type>* unbalancedNode;

	if (pos->left_Child == nullptr) 
	{
		replacingNode = pos->right_Child;
		if (pos->parent == nullptr) 
		{
			this->root = replacingNode;
			if (replacingNode != nullptr) 
			{
				replacingNode->parent = nullptr;
			}
		}
		else 
		{
			pos->parent->left_Child == pos ? pos->parent->left_Child = replacingNode : pos->parent->right_Child = replacingNode;
			if (replacingNode != nullptr) replacingNode->parent = pos->parent;
		}
		unbalancedNode = pos->parent;
		delete pos;
		pos = nullptr;
	}
	else if(pos->left_Child->right_Child == nullptr){
		replacingNode = pos->left_Child;
		if (pos->parent == nullptr) 
		{
			this->root = replacingNode;
			replacingNode->parent = nullptr;
			replacingNode->right_Child = pos->right_Child;
			if (pos->right_Child != nullptr) 
			{
				pos->right_Child->parent = replacingNode;
			}
		}
		else 
		{
			(pos->parent->left_Child == pos ? pos->parent->left_Child : pos->parent->right_Child) = replacingNode;
			replacingNode->parent = pos->parent;
			replacingNode->right_Child = pos->right_Child;
			if (pos->right_Child != nullptr) 
			{
				pos->right_Child->parent = replacingNode;
			}
		}
		unbalancedNode = replacingNode;
		delete pos;
		pos = nullptr;
	}
	else
	{
		replacingNode = pos->left_Child;
		while (replacingNode->right_Child != nullptr)
		{
			replacingNode = replacingNode->right_Child;
		}
		pos->value = replacingNode->value;
		unbalancedNode = replacingNode->parent;
		replacingNode->parent->right_Child = replacingNode->left_Child;
		if (replacingNode->left_Child != nullptr)replacingNode->left_Child->parent = replacingNode->parent;
		delete replacingNode;
		replacingNode = nullptr;
	}
	this->UpdateHeight(*unbalancedNode);
	Tree_node<type>* ancestorNode = unbalancedNode;	//ɾ���ڵ�����Ƚ��
	while (ancestorNode != nullptr)
	{	//����ɾ���������ܻ�����ʧ�⴫��������Ҫһֱ���ϼ���Ƿ�ʧ��
		if (abs(CalculateBF(*ancestorNode)) > 1)
		{	//��ʧ��ֵ�ľ���ֵ����1ʱ������ת����
			Rotate(*ancestorNode);
		}
		ancestorNode = ancestorNode->parent;
	}
	return true;

}

template<class type>
inline Tree_node<type>* AVTree<type>::Merge(AVTree* other_tree)
{
	/*
	 * �˳�����ɶ����������ĺϲ�
	 */
	Tree_node<type>* t1 = this->root;
	Tree_node<type>* t2 = other_tree->root;
	vector<type> a1, a2, a_merge;
	BinTree<type>::Bintree2Array(t1, a1);
	BinTree<type>::Bintree2Array(t2, a2);
	int i_a1 = 0, i_a2 = 0;
	while (i_a1 < a1.size() || i_a2 < a2.size())
	{
		if (i_a1 < a1.size() && i_a2 < a2.size())
		{
			if (a1[i_a1] <= a2[i_a2])
			{
				a_merge.push_back(a1[i_a1]);
				i_a1++;
			}
			else {
				a_merge.push_back(a2[i_a2]);
				i_a2++;
			}

		}
		else if (i_a1 >= a1.size())
		{
			a_merge.push_back(a2[i_a2]);
			i_a2++;
		}
		else if (i_a2 >= a2.size())
		{
			a_merge.push_back(a1[i_a1]);
			i_a1++;
		}
	}
	Tree_node<type>* t3 = new Tree_node<type>();;
	BinTree<type>::Array2Bintree(a_merge, 0, a_merge.size() - 1, t3);
	return t3;
}

template<class type>
inline void AVTree<type>::PreorderTraverse(Tree_node<type>* node, vector<type>& results)
{
	results.push_back(node->value);
	if (node->left_Child) PreorderTraverse(node->left_Child, results);	
	if (node->right_Child) PreorderTraverse(node->right_Child, results);
}

template<class type>
inline void AVTree<type>::InorderTraverse(Tree_node<type>* node, vector<type>& results)
{
	if (node->left_Child) InorderTraverse(node->left_Child, results);
	results.push_back(node->value);
	if (node->right_Child) InorderTraverse(node->right_Child, results);
}

template<class type>
inline void AVTree<type>::PostorderTraverse(Tree_node<type>* node, vector<type>& results)
{
	if (node->left_Child) PostorderTraverse(node->left_Child, results);
	if (node->right_Child) PostorderTraverse(node->right_Child, results);
	results.push_back(node->value);
}

template<class type>
inline vector<type> AVTree<type>::BFS()
{
	/*
	 * ��α���
	 */
	queue<Tree_node<type>*> bfs_queue;
	vector<type> result;
	Tree_node<type>* node;
	bfs_queue.push(this->root);
	while (!bfs_queue.empty())
	{
		int i = bfs_queue.size();
		while (i > 0 && !bfs_queue.empty())
		{
			node = bfs_queue.front();
			bfs_queue.pop();
			i--;
			result.push_back(node->value);
			if (node->left_Child) bfs_queue.push(node->left_Child);
			if (node->right_Child) bfs_queue.push(node->right_Child);
		}
	}
	return result;
}

template<class type>
inline vector<type> AVTree<type>::DFS()
{
	stack<Tree_node<type>*> dfs_stack;
	vector<type> result;
	Tree_node<type>* node;
	dfs_stack.push(this->root);
	while (!dfs_stack.empty()) 
	{
		node = dfs_stack.top();
		dfs_stack.pop();
		result.push_back(node->value);
		if (node->right_Child) dfs_stack.push(node->right_Child);
		if (node->left_Child) dfs_stack.push(node->left_Child);
	}
	return result;
}




template<class type>
inline int AVTree<type>::CalculateBF(Tree_node<type>& node)
{
	int leftChildTree_height = (node.left_Child != nullptr ? node.left_Child->height : 0);
	int rightChildTree_height = (node.right_Child != nullptr ? node.right_Child->height : 0);
	return leftChildTree_height - rightChildTree_height;
}

template<class type>
inline void AVTree<type>::Rotate(Tree_node<type>& node)
{
	int bf_v = CalculateBF(node);
	if (bf_v > 0) {
		//ʧ��ֵ����0�����������������ߣ�������ת
		if (CalculateBF(*node.left_Child) >= 0) {
			Tree_node<type>* L_node = node.left_Child;
			Tree_node<type>* LL_node = node.left_Child->left_Child;
			Tree_node<type>* LR_node = node.left_Child->right_Child;
			Tree_node<type>* R_node = node.right_Child;
			Tree_node<type>* N_node = &node;
			//Tree_node<type>* RL_node = node.right_Child->left_Child;
			//Tree_node<type>* RR_node = node.right_Child->right_Child;
			L_node->parent = node.parent;
			if (N_node->parent != nullptr) {
				if (N_node->parent->left_Child == N_node) {
					N_node->parent->left_Child = L_node;
				}
				else {
					N_node->parent->right_Child = L_node;
				}
			}
			else {
				this->root = L_node;
			}
			Connect34(L_node, LL_node, N_node, LL_node->left_Child, LL_node->right_Child, LR_node, R_node);
		}
		else {
			Tree_node<type>* L_node = node.left_Child;
			Tree_node<type>* LR_node = node.left_Child->right_Child;
			Tree_node<type>* N_node = &node;
			LR_node->parent = N_node->parent;
			if (N_node->parent != nullptr) {
				if (N_node->parent->left_Child == N_node) {
					N_node->parent->left_Child = LR_node;
				}
				else {
					N_node->parent->right_Child = LR_node;
				}
			}
			else {
				this->root = L_node;
			}
			Connect34(LR_node, L_node, N_node,
				L_node->left_Child, LR_node->left_Child, LR_node->right_Child, N_node->right_Child);
		}
	}
	else if(bf_v < 0){
		//ʧ��ֵС��0�����������������ߣ�������ת
		if (CalculateBF(*node.right_Child) <= 0) {
			Tree_node<type>* R_node = node.right_Child;
			Tree_node<type>* RR_node = node.right_Child->right_Child;
			Tree_node<type>* N_node = &node;
			R_node->parent = N_node->parent;
			if (N_node->parent != nullptr) {
				if (N_node->parent->left_Child == N_node) {
					N_node->parent->left_Child = R_node;
				}
				else {
					N_node->parent->right_Child = R_node;
				}
			}
			else {
				this->root = R_node;
			}
			Connect34(R_node, N_node, RR_node, 
				N_node->left_Child, R_node->left_Child, RR_node->left_Child, RR_node->right_Child);
		}
		else {
			Tree_node<type>* R_node = node.right_Child;
			Tree_node<type>* RL_node = node.right_Child->left_Child;
			Tree_node<type>* N_node = &node;
			RL_node->parent = N_node->parent;
			if (N_node->parent != nullptr) {
				if (N_node->parent->left_Child == N_node) {
					N_node->parent->left_Child = RL_node;
				}
				else {
					N_node->parent->right_Child = RL_node;
				}
			}
			else {
				this->root = RL_node;
			}
			Connect34(RL_node,N_node, R_node, 
				N_node->left_Child, RL_node->left_Child,RL_node->right_Child, R_node->right_Child);
		}
	}
}

template<class type>
inline void AVTree<type>::Connect34(Tree_node<type>* N, Tree_node<type>* L, Tree_node<type>* R, Tree_node<type>* LL, Tree_node<type>* LR, Tree_node<type>* RL, Tree_node<type>* RR)
{
	N->left_Child = L;
	N->right_Child = R;
	L->parent = N;
	R->parent = N;

	L->left_Child = LL;
	if (LL) LL->parent = L;
	L->right_Child = LR;
	if (LR) LR->parent = L;
	R->left_Child = RL;
	if (RL) RL->parent = R;
	R->right_Child = RR;
	if (RR) RR->parent = R;

	this->UpdateHeight(*N);
	this->UpdateHeight(*L);
	this->UpdateHeight(*R);
}
