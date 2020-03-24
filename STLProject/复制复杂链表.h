#pragma once
#include <iostream>
#include <map>
using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode* next, * random;
    RandomListNode(int x) :
        label(x), next(NULL), random(NULL) {
    }
};
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        if (pHead == NULL) {
            return NULL;
        }
        RandomListNode* new_pHead = new RandomListNode(0);
        std::map<int, RandomListNode*> _map;
        for (RandomListNode* old_p = pHead, *new_p = new_pHead; old_p != NULL; old_p = old_p->next, new_p = new_p->next) {
            RandomListNode* tmp_node = new RandomListNode(old_p->label);
            _map[tmp_node->label] = tmp_node;
            new_p->next = tmp_node;
        }
        new_pHead = new_pHead->next;
        for (RandomListNode* old_p = pHead, *new_p = new_pHead; old_p != NULL; old_p = old_p->next, new_p = new_p->next) {
            if (old_p->random != NULL) {
                new_p->random = _map[old_p->random->label];
            }
        }
        return new_pHead;
    }
    RandomListNode* Clone2(RandomListNode* pHead)
    {
        if (pHead == NULL) {
            return NULL;
        }
        std::map<RandomListNode*, RandomListNode*> _map;
        for (RandomListNode* p = pHead; p != NULL; p = p->next) {
            _map[p] = new RandomListNode(p->label);
        }
        for (RandomListNode* p = pHead; p != NULL; p = p->next) {
            _map[p]->next = _map[p->next];
            _map[p]->random = _map[p->random];
        }
        return _map[pHead];
    }
};
