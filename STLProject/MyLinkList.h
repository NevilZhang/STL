#pragma once
#include <iostream>

using namespace std;

template<class type> struct link_node {
	type value;
	link_node* front;
	link_node* back;
	link_node(type data) :value(data), front(NULL), back(NULL) {};
	~link_node() {
		front = NULL;
		back = NULL;
	}
};

template<class type>
class MyLinkList{
	link_node<type>* head_node;
	link_node<type>* tail_node;
	int size;
	MyLinkList():size(-1) {
		head_node = NULL;
		tail_node = NULL;
	}
	~MyLinkList() {
		if (Size() > 1) {
			delete head_node;
			delete tail_node;
		}
		else if(Size() == 1){
			delete head_node;
		}
		head_node = tail_node = NULL;
		size = -1;
	}
	int Size() {
		return size + 1;
	}
};

