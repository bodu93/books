#include <assert.h>
#include <list.h>

// operator <
bool lessThan(ListNode* lhs, ListNode* rhs) {
	// nullptr < nullptr
	if (lhs == nullptr && rhs == nullptr) return false;
	else if (lhs == nullptr) return false;
	else if (rhs == nullptr) return true;
	else {
		assert(lhs && rhs);
		return lhs->value < rhs->value;
	}

	assert(false);
	return false;
}


ListNode* Merge(ListNode* listHead1, ListNode* listHead2) {
	if (listHead1 == nullptr) return listHead2;
	if (listHead2 == nullptr) return listHead1;

	ListNode* newHead = nullptr;
	ListNode* newTail = nullptr;

	while (listHead1 != nullptr || listHead2 != nullptr) {
		while (listHead1 != nullptr &&
					 lessThan(listHead1, listHead2)) {
			ListNode* tmpNode = listHead1;
			listHead1 = listHead1->next;

			if (newHead == nullptr) {
				newHead = tmpNode;
				newTail = tmpNode;
			} else {
				newTail->next = tmpNode;
				newTail = newTail->next;
			}
		}

		while (listHead2 != nullptr &&
					 !lessThan(listHead1, listHead2)) {
			ListNode* tmpNode = listHead2;
			listHead2 = listHead2->next;

			if (newHead == nullptr) {
				newHead = tmpNode;
				newTail = tmpNode;
			} else {
				newTail->next = tmpNode;
				newTail = newTail->next;
			}
		}
	}
	newTail->next = nullptr;

	assert(newHead != nullptr);
	return newHead;
}

int main() {
	int list1[] = { 1, 1, 1 };
	int list2[] = { 2, 2, 2 };

	ListNode* l1 = createList(list1, sizeof(list1) / sizeof(int));
	ListNode* l2 = createList(list2, sizeof(list2) / sizeof(int));
	printList("l1: ", l1);
	printList("l2: ", l2);

	ListNode* mm = Merge(l1, l2);
	printList("after merge l1 and l2: ", mm);

	destroyList(mm);

	return 0;
}
