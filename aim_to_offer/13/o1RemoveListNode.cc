#include "../include/list.h"
#include <stdlib.h>

void DeleteNode(ListNode** listHead, ListNode* nodeToBeDeleted) {
	if (listHead == NULL || *listHead == NULL || nodeToBeDeleted == NULL)
		return;

	if (nodeToBeDeleted->next == NULL) {
		ListNode* beforeDeleted = *listHead;
		while (beforeDeleted->next != NULL &&
					 beforeDeleted->next != nodeToBeDeleted) {
			beforeDeleted = beforeDeleted->next;
		}

		if (beforeDeleted == *listHead ||
				beforeDeleted->next == nodeToBeDeleted) {
			beforeDeleted->next = nodeToBeDeleted->next;
			delete nodeToBeDeleted;
			if (*listHead == nodeToBeDeleted) *listHead = NULL;
		}
	} else {
		// overwrite nodeToBeDeleted->value
		nodeToBeDeleted->value = nodeToBeDeleted->next->value;

		// remove nodeToBeDeleted->next
		ListNode* tmpNode = nodeToBeDeleted->next->next;
		delete nodeToBeDeleted->next;
		nodeToBeDeleted->next = tmpNode;
	}
}

// standard solution from book "aim to offer"
void DeleteNode_FromBook(ListNode** pListHead, ListNode* pToBeDeleted) {
	if (!pListHead || !pToBeDeleted) return;

	if (pToBeDeleted->next != nullptr) {
		ListNode* pNext = pToBeDeleted->next;
		pToBeDeleted->value = pNext->value;
		pToBeDeleted->next = pNext->next;

		delete pNext;
		pNext = nullptr;
	} else if (*pListHead == pToBeDeleted) {
		delete pToBeDeleted;
		pToBeDeleted = nullptr;
		*pListHead = nullptr;
	} else {
		ListNode* pNode = *pListHead;
		while (pNode->next != nullptr &&
					 pNode->next != pToBeDeleted) {
			pNode = pNode->next;
		}

		if (pNode->next == pToBeDeleted) {
			pNode->next = nullptr;
			delete pToBeDeleted;
			pToBeDeleted = nullptr;
		}
	}
}

int main() {
	int ilist[] = { 1, 2, 3, 4 };
	ListNode* head = createList(ilist, sizeof(ilist) / sizeof(int));
	ListNode* nodeToBeDeleted = head->next;
	printList("before delete: ", head);
	DeleteNode(&head, nodeToBeDeleted);
	printList("after deleted: ", head);
	destroyList(head);

	return 0;
}
