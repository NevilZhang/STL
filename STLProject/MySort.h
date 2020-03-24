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
	vector<type> InsertionSort();//ֱ�Ӳ���
	vector<type> InsertionSort2();//�۰����
	vector<type> ShellSort();//ϣ������
	
	vector<type> SelectionSort();//ѡ������
	vector<type> BubbleSort();//ð������
	vector<type> MergeSort();//�鲢����
	void QuickSort(vector<type> &s, int l, int r);//��������
	vector<type> HeapSort();//������
	vector<type> RadixSort();//��������
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

	//��������
	if (l < r)
	{
		//Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ�������� �μ�ע1
		int i = l, j = r, x = s[l];
		while (i < j)
		{
			while (i < j && s[j] >= x) // ���������ҵ�һ��С��x����
				j--;
			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] < x) // ���������ҵ�һ�����ڵ���x����
				i++;
			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;
		QuickSort(s, l, i - 1); // �ݹ���� 
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
