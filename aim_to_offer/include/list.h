#ifndef LIB_LIST_H
#define LIB_LIST_H

#include <stddef.h>

struct ListNode {
	int value;
	ListNode* next;
};

ListNode* createNode(int value);

ListNode* createList(int* iarray, size_t s);

void destroyList(ListNode* head);

void printList(const char* prompt, ListNode* listHead);

#endif // LIB_LIST_H
