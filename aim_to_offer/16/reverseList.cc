#include "../include/list.h"
#include <assert.h>
#include <iostream>

ListNode* reverseList(ListNode* listHead) {
	if (!listHead || !(listHead->next)) return listHead;

	ListNode* curp = listHead;
	ListNode* nextp = curp->next;
	curp->next = nullptr;

	while (nextp) {
		ListNode* tmp = nextp->next;
		nextp->next = curp;

		curp = nextp;
		nextp = tmp;
	}

	return curp;
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
