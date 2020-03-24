#pragma once
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template<class type> 
class MySort {
private:
	vector<type> datas;
public:
	MySort();
	MySort(vector<type> ini_datas);
	void Print();
	vector<type> InsertionSort();//直接插入
	vector<type> InsertionSort2();//折半插入
	vector<type> ShellSort();//希尔排序
	
	vector<type> SelectionSort();//选择排序
	vector<type> BubbleSort();//冒泡排序
	vector<type> MergeSort();//归并排序
	void QuickSort(vector<type> &s, int l, int r);//快速排序
	vector<type> HeapSort();//堆排序
	vector<type> RadixSort();//基数排序
};

template<class type>
inline MySort<type>::MySort()
{
}

template<class type>
inline MySort<type>::MySort(vector<type> ini_datas)
{
	datas = ini_datas;
}

template<class type>
inline void MySort<type>::Print()
{
	for (vector<int>::iterator iter = datas.begin(); iter != datas.end(); iter++) {
		cout << *iter<<" ";
	}
	cout << endl;
}

template<class type>
inline vector<type> MySort<type>::InsertionSort()
{
	for (int i = 1; i < datas.size(); i++) {
		if (datas[i] < datas[i - 1]) {
			type tmp = datas[i];
			for (int j = i; j > 0; j--) {
				if (tmp < datas[j - 1]) {
					datas[j] = datas[j - 1];
				}
				else {
					datas[j] = tmp;
					break;
				}
			}
		}
	}
	return datas;
}

template<class type>
inline vector<type> MySort<type>::InsertionSort2()
{
	for (int i = 1; i < datas.size(); i++) {
		int low = 0;
		int high = i - 1;
		while (low <= high) {
			int m = (low + high) / 2;
			if (datas[i] <= datas[m]) {
				high = m - 1;
			}
			else {
				low = m + 1;
			}
		}
		type tmp = datas[i];
		for (int j = i; j >= high+1; j--) {
			datas[j] = datas[j - 1];
		}
		datas[high + 1] = tmp;
	}
	return datas;
}

template<class type>
inline vector<type> MySort<type>::ShellSort()
{
	for (int gap = datas.size() / 2; gap > 0; gap /= 2)
	{
		for (int i = 0; i < gap; i++) 
		{
			for (int j = i + gap; j < datas.size(); j+=gap)
			{
				if (datas[j] < datas[j - gap]) 
				{
					type tmp = datas[j];
					for (int k = j; k >= i;k-=gap) {
						if (k > i && tmp < datas[k-gap]){
							datas[k] = datas[k - gap];
						}
						else {
							datas[k] = tmp;
							break;
						}
					}
				}
			} 
		}
	}
	return datas;
}

template<class type>
inline vector<type> MySort<type>::SelectionSort()
{

	return vector<type>();
}

template<class type>
inline vector<type> MySort<type>::BubbleSort()
{

	return vector<type>();
}

template<class type>
inline vector<type> MySort<type>::MergeSort()
{
	return vector<type>();
}

template<class type>
inline void MySort<type>::QuickSort(vector<type>& s, int l, int r)
{

	//快速排序
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 参见注1
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x) // 从右向左找第一个小于x的数
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		QuickSort(s, l, i - 1); // 递归调用 
		QuickSort(s, i + 1, r);
	}
}

template<class type>
inline vector<type> MySort<type>::HeapSort()
{
	return vector<type>();
}

template<class type>
inline vector<type> MySort<type>::RadixSort()
{
	return vector<type>();
}
