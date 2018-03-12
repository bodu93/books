#include <list.h>
#include <stack>
#include <iostream>

void printListReversingly(ListNode* head) {
	std::stack<ListNode*> nodes;

	ListNode* node = head;
	while (node != NULL) {
		nodes.push(node);
		node = node->next;
	}

	while (!nodes.empty()) {
		ListNode* cur = nodes.top();
		nodes.pop();

		std::cout << cur->value << " ";
	}
}

int main() {
	int ilist[] = { 1, 2, 3, 4 };
	ListNode* il = createList(ilist, sizeof(ilist) / sizeof(int));
	printListReversingly(il);
	destroyList(il);

	return 0;
}
