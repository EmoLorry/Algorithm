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
//使用栈来模拟实现中序输出
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
	cout << "输入生成二叉搜索树的序列，输入任意非数字字符结束" << endl;
	BinaryTreeNode<int>* root1 = nullptr;
    while (cin >> t)
        insertIntoBST(root1, t);
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    cout << "树型及升序输出为"<<endl;
    LevelOrder(root1);
    InOrderNonRecursive(root1);

 //第二问
    string p;
    cout << "按照层序逻辑输入数字或#表示非空结点或空结点，输入任意非#且非数字字符结束"<<endl;
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
    //我们按照我们的输入方式生成了树根节点root2
    //下面进行搜索操作！
    int K = 0;
    cin >> K;
    root2->printAllPaths(K);



	return 0;
}