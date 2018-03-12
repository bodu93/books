#include "../include/list.h"
#include <assert.h>
#include <iostream>

ListNode* createNode(int value) {
	ListNode* node = new ListNode;
	node->value = value;
	node->next = nullptr;
	return node;
}

ListNode* createList(int* iarray, size_t s) {
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	ListNode* node = nullptr;

	for (size_t i = 0; i < s; ++i) {
		node = createNode(iarray[i]);
		if (head == nullptr) {
			head = node;
			tail = node;
		} else {
			tail->next = node;
			tail = node;
		}
	}

	return head;
}

void destroyList(ListNode* head) {
	while (head) {
		ListNode* node = head;
		head = head->next;
		delete node;
	}
}

void printList(const char* prompt, ListNode* listHead) {
	std::cout << prompt;
	while (listHead) {
		std::cout << listHead->value << " -> ";
		listHead = listHead->next;
	}
	std::cout << std::endl;
}
