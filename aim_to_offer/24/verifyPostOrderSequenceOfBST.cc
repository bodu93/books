#include <assert.h>
#include <stddef.h>
#include <iostream>

bool verifyPostOrderSequenceOfBST(int* sequence, int length) {
	if (sequence == nullptr || length <= 0) return false;

	assert(length >= 1);
	int root_rank = length - 1;
	int root = sequence[root_rank];

	int first_lc_rank = 0;
	int first_rc_rank = first_lc_rank;
	bool lresult = true;
	while (first_rc_rank < root_rank && sequence[first_rc_rank] < root) {
		++first_rc_rank;
	}
	if (first_rc_rank - first_lc_rank > 0) {
		lresult = verifyPostOrderSequenceOfBST(
				&sequence[first_lc_rank], first_rc_rank - first_lc_rank);
	}
	if (!lresult) return false;

	bool rresult = true;
	size_t rc_rank = first_rc_rank;
	if (root_rank - first_rc_rank > 0) {
		while (rc_rank < root_rank) {
			if (sequence[rc_rank] <= root) {
				rresult = false;
				break;
			}
			++rc_rank;
		}
		if (!rresult) return false;
		else {
			rresult = verifyPostOrderSequenceOfBST(
					&sequence[first_rc_rank], root_rank - first_rc_rank);
		}
	}

	return rresult;
}

int main() {
	// int itree[] = { 7, 4, 6, 5 };
	// int itree[] = { 5, 7, 6, 9, 11, 10, 8 };
	// int itree[] = { 1, 3, 2 };
	// int itree[] = { 2, 1, 5, 4, 6, 3 };
	int itree[] = { 1 };
	size_t len = sizeof(itree) / sizeof(int);

	bool isPostOrder = verifyPostOrderSequenceOfBST(itree, len);
	std::cout <<
		(isPostOrder ? "is post order" : "is not post order") << std::endl;

	return 0;
}
