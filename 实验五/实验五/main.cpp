#include "BinaryTree.cpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include "Stack.cpp"
using namespace std;
template<class T>
void insertIntoBST(BinaryTreeNode<T>*& root,T key) {
    BinaryTreeNode<T>* newNode = new BinaryTreeNode<T>(key);

    if (root == nullptr) {
        root = newNode;
        return;
    }

    BinaryTreeNode<T>* current = root;
    while (true) {
        if (key < current->data) {
            if (current->LeftChild == nullptr) {
                current->LeftChild = newNode;
                break;
            }
            else {
                current = current->LeftChild;
            }
        }
        else {
            if (current->RightChild == nullptr) {
                current->RightChild = newNode;
                break;
            }
            else {
                current = current->RightChild;
            }
        }
    }
}
//ʹ��ջ��ģ��ʵ���������
template<class T>
void InOrderNonRecursive(BinaryTreeNode<T>* root) {
    if (root == nullptr) {
        return;
    }

    Stack<BinaryTreeNode<T>*> stack;
    BinaryTreeNode<T>* current = root;

    while (current != nullptr || !stack.IsEmpty()) {
        while (current != nullptr) {
            stack.Add(current);
            current = current->LeftChild;
        }

        current = stack.Top();
        stack.Delete();

        std::cout << current->data << " ";

        current = current->RightChild;
    }
}

int main() {
	int t = 0;
	cout << "�������ɶ��������������У���������������ַ�����" << endl;
	BinaryTreeNode<int>* root1 = nullptr;
    while (cin >> t)
        insertIntoBST(root1, t);
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "���ͼ��������Ϊ"<<endl;
    LevelOrder(root1);
    InOrderNonRecursive(root1);

 //�ڶ���
    string p;
    cout << "���ղ����߼��������ֻ�#��ʾ�ǿս���ս�㣬���������#�ҷ������ַ�����"<<endl;
    LinkedQueue<BinaryTreeNode<int>*> nodesQueue;
    BinaryTreeNode<int> * root2 = nullptr;
    while (cin >> p) {
        if (!(('0' <= p[0] && p[0] <= '9')||p[0]=='-' || p[0] == '#'))
            break;
        else {
            BinaryTreeNode<int>* newnode = nullptr;
            if(p[0]!='#')
               newnode = new BinaryTreeNode<int>(std::stoi(p));
    
            if(!root2)
            {
                root2 = newnode;
                nodesQueue.Add(root2);
            }
                
            else {
                if (!nodesQueue.IsEmpty())
                {
                    while ((nodesQueue.First()->isLeftinitialized) && (nodesQueue.First()->isRightinitialized))
                    {
                        nodesQueue.Delete();
                    }

                    if (nodesQueue.First()->isLeftinitialized == 0)
                    {
                        nodesQueue.First()->isLeftinitialized = 1;
                        if (newnode)
                        {
                            nodesQueue.First()->LeftChild = newnode;
                            nodesQueue.Add(newnode);
                        }
                        else
                        {
                            nodesQueue.First()->LeftChild = newnode;
                        }
                    }
                    else
                    {
                        nodesQueue.First()->isRightinitialized = 1;
                        if(newnode)
                        {
                        nodesQueue.First()->RightChild = newnode;
                        nodesQueue.Add(newnode);
                        }
                        else
                        {
                            nodesQueue.First()->RightChild = newnode;
                        }
                    }
                }
            }
           
        }
        //LevelOrder(root2);
    }
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.clear();

    if (!root2)
        cout << "NONE";
    LevelOrder(root2);
    //���ǰ������ǵ����뷽ʽ�����������ڵ�root2
    //�����������������
    int K = 0;
    cin >> K;
    root2->printAllPaths(K);



	return 0;
}