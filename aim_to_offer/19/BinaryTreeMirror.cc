/*
 * 请完成一个函数，输入一个二叉树，该函数输出它的镜像
 */

#include <stack>

struct BinaryTreeNode {
	int 										m_nValue;
	BinaryTreeNode*					m_pLeft;
	BinaryTreeNode*					m_pRight;
};

void swapChilds(BinaryTreeNode* &node) {
	BinaryTreeNode* tmpNode = node->m_pLeft;
	node->m_pLeft = node->m_pRight;
	node->m_pRight = tmpNode;
}

void MirrorRecursively(BinaryTreeNode* pNode) {
	// recursion base
	if (pNode == NULL) return;
	if (pNode->m_pLeft == NULL && pNode->m_pRight == NULL) return;

	// do swap
	swapChilds(pNode);

	if (pNode->m_pLeft) MirrorRecursively(pNode->m_pLeft);
	if (pNode->m_pRight) MirrorRecursively(pNode->m_pRight);
}

void MirrorIteratively(BinaryTreeNode* pNode) {
	/*
	 * from the recursion version of
	 * function, we can find it is just a
	 * inorder traverse
	 */
	if (pNode == NULL) return;
	std::stack<BinaryTreeNode*> nodes;
	nodes.push(pNode);

	while (!nodes.empty()) {
		BinaryTreeNode* node = nodes.top();
		nodes.pop();
		swapChilds(node);
		if (node->m_pRight != NULL) nodes.push(node->m_pRight);
		if (node->m_pLeft != NULL) nodes.push(node->m_pLeft);
	}
}

int main() {
	return 0;
}
