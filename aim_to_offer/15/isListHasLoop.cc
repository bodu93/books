#include <list.h>
#include <assert.h>

bool isListHasLoop(ListNode* listHead) {
	if (listHead == nullptr) return false;

	ListNode* slowp = listHead;
	ListNode* fastp = listHead;

	bool result = false;
	while (slowp != nullptr && fastp != nullptr) {
		slowp = slowp->next;
		fastp = fastp->next;
		if (fastp != nullptr) fastp = fastp->next;

		if (fastp == slowp && fastp != nullptr) {
			result = true;
			break;
		}
	}

	return result;
}

ListNode* createListNode(int value) {
	ListNode* node = new ListNode;
	node->value = value;
	node->next = nullptr;
	return node;
}

int main() {
	// odd nodes
	ListNode* head = createListNode(1);
	assert(isListHasLoop(head) == false);

	// even nodes
	ListNode* snode = createListNode(2);
	head->next = snode;
	snode->next = head;
	assert(isListHasLoop(head) == true);

	return 0;
}
