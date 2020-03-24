#pragma once
#include <iostream>

#define MAXSIZE 0xffff

using namespace std;

template<class type>
class MyStack
{
	int top;
	type* values;
	int maxsize;

public:
	MyStack();
	MyStack(int size);
	~MyStack();

	bool Empty();
	void Push(type top_value);
	type Top();
	void Pop();
	int Size();
};

template<class type>
inline MyStack<type>::MyStack() :top(-1), maxsize(MAXSIZE)
{
	values = new type[MAXSIZE];
	if (values == NULL) {
		std::cerr << "ÄÚ´æÉêÇë´íÎó" << endl;
		exit(1);
	}
}

template<class type>
inline MyStack<type>::MyStack(int size) :top(-1), maxsize(size)
{
	values = new type[maxsize];
	if (values == NULL) {
		std::cerr << "ÄÚ´æÉêÇë´íÎó" << endl;
		exit(1);
	}
}

template<class type>
inline MyStack<type>::~MyStack()
{
	delete values;
}

template<class type>
bool MyStack<type>::Empty()
{
	if (top == -1) {
		return true;
	}
	else {
		return false;
	}
}

template<class type>
void MyStack<type>::Push(type top_value)
{
	if (top + 1 < maxsize) {
		values[++top] = top_value;
	}
	else {
		std::cerr << "Õ»Âú" << endl;
		exit(1);
	}
}

template<class type>
type MyStack<type>::Top()
{
	if (top != -1)
		return values[top];
	else {
		std::cout << "Õ»¿Õ" << endl;
		exit(1);
	}
}

template<class type>
void MyStack<type>::Pop()
{
	if (top != -1) {
		top--;
	}
	else {
		std::cout << "Õ»¿Õ" << endl;
		exit(1);
	}
}

template<class type>
int MyStack<type>::Size()
{
	return top + 1;
}
