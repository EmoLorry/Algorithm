#include "BinaryTree.cpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
int main()
{
	//��һ��
	cout << "������ǰ���������������ĸ����" << endl;
	int t = 0;
	vector<int> preorder;
	while (cin >> t) {
		preorder.push_back(t);
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cout << "�����������������������ĸ����" << endl;
	vector<int> inorder;
	while (cin >> t) {
		inorder.push_back(t);
	}
	BinaryTreeNode<int>* root = BuildTreeFromTraversal(preorder, inorder);
	cout << "Level Order Traversal: " << endl;
	LevelOrder(root);

	//�ڶ���
	BinaryTree<int> TreeUnchanged(root);
	//TreeUnchanged.LevelOrderTree();

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	int p = 0; cout << "Ҫ���ҵĽڵ�ؼ���Ϊ:"; 
	cin >> p;
	cout << "�ڵ�߶�Ϊ" << TreeUnchanged.NodeHeightinTree(p) << endl;
	if (!TreeUnchanged.FindParentNode(p))
		cout << "�ùؼ��ִ��ڸ��ڵ㣬�����任������" << endl;
	else
	{
		cout << "�ڵ�ĸ��ڵ�ؼ���Ϊ" << TreeUnchanged.FindParentNode(p)->data << endl;
		TreeUnchanged.rotate(TreeUnchanged.FindNode(p), TreeUnchanged.FindParentNode(p));
		cout << "����������ת�任��Ķ�����������Ϊ��" << endl;
		TreeUnchanged.LevelOrderTree();
	}

	//������
	cout << "�ж��Ƿ�Ϊ��ȫ������:";
	if (TreeUnchanged.isCompleteBinaryTree())
		cout << "����ȫ��������";
	else
	{
		cout << "������ȫ��������" << endl;
		cout << "ת�������ȫ�������������Ϊ" << endl;
		BinaryTree<int> Treechanged(TreeUnchanged.ConvertToFullBinaryTree());
		Treechanged.LevelOrderTree();
	}
	return 0;
}

