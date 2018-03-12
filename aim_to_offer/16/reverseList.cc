#include "../include/list.h"
#include <assert.h>
#include <iostream>

ListNode* reverseList(ListNode* listHead) {
	if (listHead == nullptr || listHead->next == nullptr) return listHead;

	ListNode* frontp = listHead;
	ListNode* backp = listHead->next;
	ListNode* nextp = nullptr;

	while (backp != nullptr) {
		nextp = backp->next;
		if (frontp == listHead) frontp->next = nullptr;
		backp->next = frontp;

		frontp = backp;
		backp = nextp;
	}

	return frontp;
}

int main() {
	int ilist[] = { 1, 2, 3, 4 };
	size_t len = sizeof(ilist) / sizeof(int);

	ListNode* head = createList(ilist, len);
	printList("before reversed: ", head);

	head = reverseList(head);
	printList("after reversed: ", head);

	destroyList(head);

	return 0;
}
