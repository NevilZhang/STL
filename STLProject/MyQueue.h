#pragma once
#include <iostream>

using namespace std;

template<class type> struct node{
	type data;
	node* next;
	node(type data) :data(data), next(NULL) {};
	~node() { next = NULL; }
};

template<class type>
class MyQueue
{
	node<type>* front;
	node<type>* back;
	int size;
public:
	MyQueue();
	~MyQueue();
	void Push(type data);
	void Pop();
	bool Empty();
	type Front();
	type Back();
	int Size();
};

template<class type>
inline MyQueue<type>::MyQueue():size(-1)
{
	front = back = NULL;
}

template<class type>
inline MyQueue<type>::~MyQueue()
{
	if (Size() > 1) {
		delete front;
		delete back;
	}
	else if(Size() == 1){
		delete front;
	}
	
	front = back = NULL;
}

template<class type>
inline void MyQueue<type>::Push(type data)
{
	node<type> *_node = new node<type>(data);
	_node->next = NULL;
	if (front == NULL) {
		front = back = _node;
	}
	else {
		back->next = _node;
		back = _node;
	}
	size++;
}

template<class type>
inline void MyQueue<type>::Pop()
{
	if (!Empty()) {
		node<type> _node = front;
		front = front->next;
		delete _node;
		size--;
	}
	else {
		cout << "空队列" << endl;
	}
}

template<class type>
inline bool MyQueue<type>::Empty()
{
	if (size > -1) {
		return false;
	}
	else {
		return true;
	}
}

template<class type>
inline type MyQueue<type>::Front()
{
	if (!Empty()) {
		return front->data;
	}
	else {
		cout << "空队列" << endl;;
	}
}

template<class type>
inline type MyQueue<type>::Back()
{
	if (!Empty()) {
		return back->data;
	}
	else {
		cout << "空队列" << endl;
	}
}

template<class type>
inline int MyQueue<type>::Size()
{
	return size + 1;
}



