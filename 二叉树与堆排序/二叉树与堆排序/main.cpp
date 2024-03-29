#include "BinaryTree.cpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int main()
{
	//第一问
	cout << "请输入前序遍历，以任意字母结束" << endl;
	int t = 0;
	vector<int> preorder;
	while (cin >> t) {
		preorder.push_back(t);
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "请输入中序遍历，以任意字母结束" << endl;
	vector<int> inorder;
	while (cin >> t) {
		inorder.push_back(t);
	}
	BinaryTreeNode<int>* root = BuildTreeFromTraversal(preorder, inorder);
	cout << "Level Order Traversal: " << endl;
	LevelOrder(root);

	//第二问
	BinaryTree<int> TreeUnchanged(root);
	//TreeUnchanged.LevelOrderTree();

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int p = 0; cout << "要查找的节点关键字为:"; 
	cin >> p;
	cout << "节点高度为" << TreeUnchanged.NodeHeightinTree(p) << endl;
	if (!TreeUnchanged.FindParentNode(p))
		cout << "该关键字处于根节点，不作变换操作！" << endl;
	else
	{
		cout << "节点的父节点关键字为" << TreeUnchanged.FindParentNode(p)->data << endl;
		TreeUnchanged.rotate(TreeUnchanged.FindNode(p), TreeUnchanged.FindParentNode(p));
		cout << "进行题述旋转变换后的二叉树逐层遍历为：" << endl;
		TreeUnchanged.LevelOrderTree();
	}

	//第三问
	cout << "判断是否为完全二叉树:";
	if (TreeUnchanged.isCompleteBinaryTree())
		cout << "是完全二叉树！";
	else
	{
		cout << "不是完全二叉树！" << endl;
		cout << "转换后的完全二叉树层序遍历为" << endl;
		BinaryTree<int> Treechanged(TreeUnchanged.ConvertToFullBinaryTree());
		Treechanged.LevelOrderTree();
	}
	return 0;
}

