// STLProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <list>
#include <string>
#include "MyQueue.h"
#include "MyStack.h"
#include "MyLinkList.h"
#include "MyAVTree.h"
#include "MySort.h"
#include "MyHashTable.h"
#include <map>
#include<cstdlib>
#include<ctime>
#include <unordered_map>
using namespace std;


clock_t start, end_t;
class Solution {
	int numSum(int i) {
		int sum = 0;
		while (i > 0) {
			sum += i % 10;
			i /= 10;
		}
		return sum;
	}
	int mc(int k, int rows, int cols, int i, int j, bool* isUsed, int* x, int* y) {
		if (i < 0 || i >= rows || j < 0 || j >= cols || isUsed[i * cols + j] || (x[j] + y[i]) > k) {
			return 0;
		}
		isUsed[i * cols + j] = true;
		return mc(k, rows, cols, i + 1, j, isUsed, x, y)
			+ mc(k, rows, cols, i - 1, j, isUsed, x, y)
			+ mc(k, rows, cols, i, j + 1, isUsed, x, y)
			+ mc(k, rows, cols, i, j - 1, isUsed, x, y);

	}
public:
	int movingCount(int threshold, int rows, int cols)
	{
		if (threshold <= 0 || (rows == 0 && cols == 0)) {
			return false;
		}
		int* x = new int[cols];
		int* y = new int[rows];
		for (int i = 0; i < rows || i < cols; i++) {
			int tmp = numSum(i);
			if (i < rows) {
				y[i] = tmp;
			}
			if (i < cols) {
				x[i] = tmp;
			}
		}
		bool* isUesd = new bool[rows * cols];
		return mc(threshold, rows, cols, 0, 0, isUesd, x, y);
	}
};
string PrintMinNumber(vector<int> numbers);
void testAVTree();
void testMergeTrees();
void testTraverseTree();
void testBFS();
void testHashTable();
void testPointer();

struct sds
{
	int len;    //buff 中已经占用的字节数
	int free;   //buff 中剩余的可用字节数
	char buff[];//数据空间，
				//柔性数组——c语言中，定义在结构体最后的一个可以不分配大小的连续空间
};

void findSumIndex(int numbers[], int target){
	int len = 4;
	if (len == 0) return;
	map<int, int> map_num;
	for (int i = 0; i < len; i++) {
		int t = target - numbers[i];
		if (map_num.count(numbers[i]) == 1) {
			cout << map_num[t] << i;
			break;
		}else {
			map_num[t] = i;
		}
	}
}

int main()
{
	int numbers[4] = { 7, 2, 11, 15 }, target = 9;
	findSumIndex(numbers, target);
	//long sz = 100000;
	//long a = 0, b = 0, c = 0;
	//start = clock();		//程序开始计时
	//long k = 123456789;
	//for (long i = 0; i < sz; i++) {
	//	for (long j = 0; j < sz; j++) {
	//		a = k % 10;
	//		b = k % 10;
	//		c = k % 10;
	//		/*a = k - int(k * 0.1) * 10;
	//		b = k - int(k * 0.1) * 10;
	//		c = k - int(k * 0.1) * 10;*/

	//	}
	//	
	//}



	//end_t = clock();		//程序结束用时
	//double endtime = (double)(end_t - start) / CLOCKS_PER_SEC;

	//cout << "Total time:" << endtime * 1000 << "ms" << endl;	//ms为单位
	//system("pause");
	/*Solution s;
	vector<int> a = { 3, 5, 1, 4, 2 };
	char b[] = "+123.23e-112";
	cout << s.movingCount(10, 1, 100);*/
	/*int a = 123;
	cout << a * 0.1 << "\n";
	cout << a / 10 << "\n";
	cout << a - int(a * 0.1) * 10 << "\n";
	cout << a % 10 << "\n";*/
	
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

string PrintMinNumber(vector<int> numbers)
{
	vector<string> num_str;
	for (auto i : numbers) {
		num_str.push_back(to_string(i));
	}
	sort(num_str.begin(), num_str.end());
	string res = "";
	for (auto i : num_str) {
		res += i;
	}
	return res;
}

void testAVTree() {
	AVTree<int>* T = new AVTree<int>();
	int a[10] = { 3,2,1,4,5,6,7,10,9,8 };
	for (int i = 0; i < 10; i++)
	{
		T->Insert(a[i]);
	}
	T->Print();
}


void testMergeTrees()
{
	AVTree<int>* T = new AVTree<int>();
	int a[10] = { 3, 2 ,1, 4 , 9};
	for (int i = 0; i < 5; i++)
	{
		T->Insert(a[i]);
	}
	AVTree<int>* T2 = new AVTree<int>();
	int a2[10] = { 6, 5 ,7, 8 };
	for (int i = 0; i < 4; i++)
	{
		T2->Insert(a2[i]);
	}
	AVTree<int> T3(T->Merge(T2));
	T3.Print();
}

void testTraverseTree()
{
	AVTree<int>* T = new AVTree<int>();
	int a[10] = { 3, 2 ,1, 4 , 9 };
	for (int i = 0; i < 5; i++)
	{
		T->Insert(a[i]);
	}
	vector<int> re;
	T->PostorderTraverse(T->root, re);
	for (int i = 0; i < 5; i++)
	{
		cout << re[i] << " ";
	}
	cout << endl;
}

void testBFS()
{
	AVTree<int>* T = new AVTree<int>();
	int a[10] = { 3, 2 ,1, 4 , 9 };
	for (int i = 0; i < 5; i++)
	{
		T->Insert(a[i]);
	}
	vector<int> re;
	re = T->DFS();
	for (int i = 0; i < 5; i++)
	{
		cout << re[i] << " ";
	}
	cout << endl;
}

void testHashTable()
{
	MyHashTable<int> hash_table;
	for(int i = 1; i <= 10;i++)
		hash_table.InsertHash(i, 10 * i);
	cout << hash_table.SearchHash(5) << endl;
}

unique_ptr<string> demo(const char* s)
{
	unique_ptr<string> temp(new string(s));
	return temp;
}
void testPointer()
{
	

	//假设编写了如下代码：
	unique_ptr<string> ps;
	ps = demo("Uniquely special");
	cout << *ps;
}
