#include <list.h>
#include <stddef.h> // size_t
#include <assert.h>

// k count from 1
ListNode* findKthToTail(ListNode* listHead, size_t k) {
	if (listHead == nullptr || k == 0) return nullptr;

	ListNode* fastp = listHead;
	ListNode* slowp = listHead;

	size_t c = 0;
	// step forward (k - 1) nodes
	while (fastp != nullptr && c < k - 1) {
		fastp = fastp->next;
		++c;
	}

	// list_length < k
	if (fastp == nullptr) return nullptr;

	while (fastp->next != nullptr) {
		++fastp;
		++slowp;
	}

	return slowp;
}

int main() {
	int ilist[] = { 1, 2, 3, 4 };
	size_t len = sizeof(ilist) / sizeof(int);

	ListNode* head = createList(ilist, len);

	ListNode* node = findKthToTail(head, 2);
	assert(node->value == 3);

	node = findKthToTail(head, 1);
	assert(node->value == 4);

	node = findKthToTail(head, 4);
	assert(node->value == 1);

	node = findKthToTail(head, 5);
	assert(node == nullptr);

	destroyList(head);

	return 0;
}
