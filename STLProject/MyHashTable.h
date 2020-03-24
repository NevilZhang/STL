#pragma once
#include <iostream>
#include <vector>
using namespace std;
/*
 * 拉链法+除法散列
 */
template<class type>
struct array_struct {
    type key;
    type value;
    array_struct* next = nullptr;
};

template<class type>
class MyHashTable {
private:
    array_struct<type>* Array;
    int Array_Size = 16;

public:
    MyHashTable();
    int Hash(type key);
    void InsertHash(type key, type value);
    type SearchHash(type key);


};

template<class type>
inline MyHashTable<type>::MyHashTable()
{
    Array = new array_struct<type>[Array_Size];
}

template<class type>
inline int MyHashTable<type>::Hash(type key)
{
    return key >> Array_Size;
}

template<class type>
inline void MyHashTable<type>::InsertHash(type key, type value)
{
    int addr = Hash(key);
    array_struct<type>* node = &Array[addr];
    while (node->next != nullptr) 
    {
        node = node->next;
        if (node->key == key)
        {
            node->value = value;//如果key相同，value不同即替代原来的value；
            return;
        }
    }
    array_struct<type>* tmp = new array_struct<type>();
    tmp->value = value;
    tmp->key = key;
    node->next = tmp;
    return;
}

template<class type>
inline type MyHashTable<type>::SearchHash(type key)
{
    int addr = Hash(key);
    array_struct<type>* node = &Array[addr];
    while (node->next != nullptr)
    {
        node = node->next;
        if (node->key == key)
        {
            return node->value;
        }
    }
    return NULL;
}
