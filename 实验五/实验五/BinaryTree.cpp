#include<iostream>
#include<vector>
#include <unordered_set>
#include <unordered_map>
#include "LinkQueue.cpp"
using namespace std;
template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode {
    friend BinaryTree<T>;
    friend void Visit(BinaryTreeNode<T>* x)
    {// Visit node *x, just output data field.
        cout << x->data << "(";
        if (x->LeftChild)
            cout << x->LeftChild->data;
        else
            cout << "#";
        cout << ",";
        if (x->RightChild)
            cout << x->RightChild->data;
        else
            cout << "#";
        cout << ")" << ' ';

    }
    friend void InOrder(BinaryTreeNode<T>* t) {// Inorder traversal of *t.
        if (t) {
            InOrder(t->LeftChild); 	//���������� 
            Visit(t); 				//���ʸ��ڵ� 
            InOrder(t->RightChild); 	//���ʸ��ڵ� 
        }
    } //����8-3��
    friend void PreOrder(BinaryTreeNode<T>* t) {// Preorder traversal of *t.
        if (t) {
            Visit(t);                 		// ���ʸ��ڵ� 
            PreOrder(t->LeftChild);    	// ���������� 
            PreOrder(t->RightChild);  	//���������� 
        }
    }//����8-2ǰ����� 
    friend void PostOrder(BinaryTreeNode<T>* t) {// Postorder traversal of *t.
        if (t) {
            PostOrder(t->LeftChild);    //���������� 
            PostOrder(t->RightChild);  //���������� 
            Visit(t);                      //���ʸ��ڵ� 
        }
    } //����8-4�������

    friend void LevelOrder(BinaryTreeNode<T>* t) {
        LinkedQueue<BinaryTreeNode<T>*> Q;
        if (!t) return;  // �������

        Q.Add(t);  // �����ڵ�������

        while (!Q.IsEmpty()) {
            int currentLevelSize = Q.Size();  // ��¼��ǰ��Ľڵ���

            for (int i = 0; i < currentLevelSize; ++i) {
                BinaryTreeNode<T>* currentNode;
                try {
                    Q.Delete(currentNode);
                }
                catch (OutOfBounds) {
                    return;
                }

                Visit(currentNode);  // ���ʽڵ�

                // ���ڵ�ĺ��Ӽ������
                if (currentNode->LeftChild) Q.Add(currentNode->LeftChild);
                if (currentNode->RightChild) Q.Add(currentNode->RightChild);
            }
            cout << endl;  // ��ÿһ���������뻻�з�
        }
    }
    friend int HeightFromNode(BinaryTreeNode<T>* node) {
        if (!node) {
            return 0;//û����Ӧ�ؼ��ֵĽڵ�
        }

        int leftHeight = HeightFromNode(node->LeftChild);
        int rightHeight = HeightFromNode(node->RightChild);

        // ���ؽڵ�ĸ߶�Ϊ���������нϴ�ĸ߶ȼ� 1
        return 1 + max(leftHeight, rightHeight);
    }

    friend BinaryTreeNode<T>* insertIntoCompleteTree(BinaryTreeNode<T>* root, int value) {
        if (root == nullptr) {
            return new BinaryTreeNode<T>(value);
        }
        LinkedQueue<BinaryTreeNode<T>*> q;
        q.Add(root);

        while (!q.IsEmpty()) {
            BinaryTreeNode<T>* current = q.First();
            q.Delete();

            if (current->LeftChild == nullptr) {
                current->LeftChild = new BinaryTreeNode<T>(value);
                break;
            }
            else if (current->RightChild == nullptr) {
                current->RightChild = new BinaryTreeNode<T>(value);
                break;
            }
            else {
                q.Add(current->LeftChild);
                q.Add(current->RightChild);
            }
        }
        return root;
    }
    friend int main();
public:
    BinaryTreeNode() {
        LeftChild = RightChild = NULL;
        isLeftinitialized = isRightinitialized = 0;
    }
    BinaryTreeNode(const T& e) {
        data = e;
        LeftChild = RightChild = 0;
        isLeftinitialized = isRightinitialized = 0;

    }
    BinaryTreeNode(const T& e,
        BinaryTreeNode* l, BinaryTreeNode* r)
    {
        data = e; LeftChild = l;  RightChild = r;
    }
    void printAllPaths(int K) {
        std::vector<T> currentPath;//������һ�����գ��������Ա�ʾ���ڵ�·��״̬���ǽ��к���������������Ļ���
        printAllPathsHelper(this, K, currentPath);
    }
    T data;
    int isLeftinitialized, isRightinitialized;
    BinaryTreeNode<T>* LeftChild, * RightChild;   //subtree
private:
    void printAllPathsHelper(const BinaryTreeNode<T>* node, int K, std::vector<T>& currentPath) const {
        if (node == nullptr) {
                return;
            }
            currentPath.push_back(node->data);
            
            for(int t=0;t<currentPath.size();t++){
              int currentScore = calculateScore(currentPath,t);
              if (currentScore == K)
              {
               std::vector<int> tempVector(currentPath.begin(), currentPath.begin() + t);
                currentPath.erase(currentPath.begin(), currentPath.begin() + t);
                printPath(currentPath);
                currentPath.insert(currentPath.begin(), tempVector.begin(), tempVector.end());
              }
            }
            printAllPathsHelper(node->LeftChild, K, currentPath);
            printAllPathsHelper(node->RightChild, K, currentPath);

            currentPath.pop_back();  // Backtrack
        }

    int calculateScore(const std::vector<T> path,int t) const {
            int score = 0;
            for (size_t i = t; i < path.size(); ++i) {
                // ÿ���ڵ�ĵ÷�Ϊ�ؼ���ֵ�����������Ĳ㼶��
                score += (i + 1) ;
                score += path[i];
            }
            return score;
        }

    void printPath(const std::vector<T> path) const {
            std::cout << "Path: ";
            for (const T& value : path) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
};

template<class T>
class BinaryTree {
public:
    BinaryTree(BinaryTreeNode<T>* root) { this->root = root; }
    BinaryTree() { root = 0; }
    ~BinaryTree() {};
    int NodeHeightinTree(const T& key) {
        return HeightFromNode(FindNode(key));
    }

    BinaryTreeNode<T>* FindNode(const T& key) {
        return FindNodeHelper(key, root);
    }
    BinaryTreeNode<T>* FindParentNode(const T& key) {
        return FindParentNodeHelper(key, nullptr, root);
    }
    BinaryTreeNode<T>* FindParentNode(const BinaryTreeNode<T>* node) {
        return FindParentNodeHelper(node, nullptr, root);
    }

    //���ɵ�ǰ����ȫ������ת��Ϊ��ȫ�������ĸ��ڵ�
    BinaryTreeNode<T>* ConvertToFullBinaryTree() {
        return ConvertHelper(root);
    }
    bool IsEmpty() const
    {
        return ((root) ? false : true);
    }
    bool Root(T& x) const;
    bool isCompleteBinaryTree() const {
        return isCompleteBinaryTree(root);
    }

    void MakeTree(const T& element,
        BinaryTree<T>& left, BinaryTree<T>& right);
    void BreakTree(T& element,
        BinaryTree<T>& left, BinaryTree<T>& right);
    void PreOrderTree()
    {
        PreOrder(this->root);
    }
    void InOrderTree()
    {
        InOrder(this->root);
    }
    void PostOrderTree()
    {
        PostOrder(this->root);
    }
    void LevelOrderTree()
    {
        LevelOrder(this->root);
    }
    void rotate(BinaryTreeNode<T>* x, BinaryTreeNode<T>* parent) {

        if (x == parent->LeftChild) { // x��parent�����ӽڵ�
            if (FindParentNode(parent) == nullptr) {  //x�任�������ڵ�

                parent->LeftChild = x->RightChild;
                x->RightChild = parent;
                root = x;
            }
            else { //x�任��Ҳ���Ǹ��ڵ�
                if (FindParentNode(parent)->LeftChild == parent)
                    FindParentNode(parent)->LeftChild = x;
                else
                    FindParentNode(parent)->RightChild = x;
                parent->LeftChild = x->RightChild;
                x->RightChild = parent;

            }
        }
        else {  // x��parent�����ӽڵ�
            if (FindParentNode(parent) == nullptr) {  //x�任�������ڵ�

                parent->RightChild = x->LeftChild;
                x->LeftChild = parent;
                root = x;
            }
            else {   //x�任��Ҳ���Ǹ��ڵ�

                if (FindParentNode(parent)->LeftChild == parent)
                    FindParentNode(parent)->LeftChild = x;
                else
                    FindParentNode(parent)->RightChild = x;
                parent->RightChild = x->LeftChild;
                x->LeftChild = parent;

            }
        }
    }

private:
    BinaryTreeNode<T>* root;  // pointer to root
    BinaryTreeNode<T>* FindNodeHelper(const T& key, BinaryTreeNode<T>* node) {
        if (!node) {
            // ����ڵ�Ϊ�գ�����nullptr��ʾδ�ҵ��ؼ���
            return nullptr;
        }

        if (node->data == key) {
            // ����ҵ��ؼ��֣����ص�ǰ�ڵ�
            return node;
        }

        // ���������в��� 
        BinaryTreeNode<T>* leftResult = FindNodeHelper(key, node->LeftChild);
        if (leftResult) {
            // ��������������ҵ��������������еĽ��
            return leftResult;
        }

        // ���������в���
        return FindNodeHelper(key, node->RightChild);
    }
    BinaryTreeNode<T>* FindParentNodeHelper(const T& key, BinaryTreeNode<T>* parent, BinaryTreeNode<T>* node) {
        if (!node) {
            // ����ڵ�Ϊ�գ�����nullptr��ʾδ�ҵ��ؼ���
            return nullptr;
        }

        if (node->data == key) {
            // ����ҵ��ؼ��֣����ظ��ڵ�
            return parent;
        }

        // ���������в���
        BinaryTreeNode<T>* leftResult = FindParentNodeHelper(key, node, node->LeftChild);
        if (leftResult) {
            // ��������������ҵ��������������еĽ��
            return leftResult;
        }

        // ���������в���
        return FindParentNodeHelper(key, node, node->RightChild);
    }
    BinaryTreeNode<T>* FindParentNodeHelper(const BinaryTreeNode<T>* targetNode, BinaryTreeNode<T>* parent, BinaryTreeNode<T>* node) {
        if (!node) {
            // ����ڵ�Ϊ�գ�����nullptr��ʾδ�ҵ�
            return nullptr;
        }

        if (node == targetNode) {
            // �ҵ�Ŀ��ڵ㣬���ظ��ڵ�
            return parent;
        }

        // ���������в���
        BinaryTreeNode<T>* leftResult = FindParentNodeHelper(targetNode, node, node->LeftChild);
        if (leftResult) {
            // ��������������ҵ��������������еĽ��
            return leftResult;
        }

        // ���������в���
        return FindParentNodeHelper(targetNode, node, node->RightChild);
    }

    BinaryTreeNode<T>* ConvertHelper(BinaryTreeNode<T>* nonCompleteRoot) {
        if (nonCompleteRoot == nullptr) {
            return nullptr;
        }

        BinaryTreeNode<T>* completeRoot = nullptr;
        LinkedQueue<BinaryTreeNode<T>*> q;
        q.Add(nonCompleteRoot);

        while (!q.IsEmpty()) {
            BinaryTreeNode<T>* current = q.First();
            q.Delete();

            completeRoot = insertIntoCompleteTree(completeRoot, current->data);





            if (current->LeftChild != nullptr) {
                q.Add(current->LeftChild);
            }
            if (current->RightChild != nullptr) {
                q.Add(current->RightChild);
            }
        }

        return completeRoot;
    }



    bool isCompleteBinaryTree(BinaryTreeNode<T>* node) const {
        if (!node)
            return true;

        // ʹ�ò����������Ƿ�������ȫ������������
        LinkedQueue<BinaryTreeNode<T>*> q;
        q.Add(node);

        while (!q.IsEmpty()) {
            BinaryTreeNode<T>* current = q.First();
            q.Delete();

            if (current) {
                q.Add(current->LeftChild);
                q.Add(current->RightChild);
            }
            else {
                // �����սڵ㣬���������Ƿ��зǿսڵ㣬����У�������ȫ������
                while (!q.IsEmpty()) {
                    if (q.First())
                        return false;
                    q.Delete();
                }
            }
        }
        return true;
    }
};

template <class T>
void Visit(BinaryTreeNode<T>* x)
{// Visit node *x, just output data field.
    cout << x->data << ' ';
}

template<class T>
bool BinaryTree<T>::Root(T& x) const
{// Return root data in x.
  // Return false if no root.
    if (root) {
        x = root->data;
        return true;
    }
    else return false;  // no root
}

template<class T>
void BinaryTree<T>::MakeTree(const T& element,
    BinaryTree<T>& left, BinaryTree<T>& right)
{ //��left,right��element�ϲ���һ������left,right��this�����ǲ�ͬ���� .
    root = new BinaryTreeNode<T>(element, left.root, right.root);
    //��ֹ����left��right 
    left.root = right.root = 0;
}

template<class T>
void BinaryTree<T>::BreakTree(T& element,
    BinaryTree<T>& left, BinaryTree<T>& right)
{//left,right��this�����ǲ�ͬ����
    if (!root) throw BadInput(); // tree empty
    //�ֽ��� 
    element = root->data;
    left.root = root->LeftChild;
    right.root = root->RightChild;
    delete root;
    root = 0;
}

template<class T>
BinaryTreeNode<T>* BuildTree(const vector<T>& preorder, const vector<T>& inorder,
    int pre_start, int pre_end, int in_start, int in_end,
    unordered_map<T, int>& inorder_map) {
    if (pre_start > pre_end || in_start > in_end) {
        return NULL;  // �ݹ���ֹ����
    }
    T root_value = preorder[pre_start];
    BinaryTreeNode<T>* root = new BinaryTreeNode<T>(root_value);

    int root_index = inorder_map[root_value];

    int left_subtree_size = root_index - in_start;
    //  int right_subtree_size = in_end - root_index;
    root->LeftChild = BuildTree(preorder, inorder, pre_start + 1, pre_start + left_subtree_size,
        in_start, root_index - 1, inorder_map);
    root->RightChild = BuildTree(preorder, inorder, pre_start + left_subtree_size + 1, pre_end,
        root_index + 1, in_end, inorder_map);

    return root;
}

template<class T>
BinaryTreeNode<T>* BuildTreeFromTraversal(const vector<T>& preorder, const vector<T>& inorder) {
    if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) {
        return NULL;
    }
    unordered_map<T, int> inorder_map;
    for (int i = 0; i < inorder.size(); ++i) {
        inorder_map[inorder[i]] = i;
    }

    return BuildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1, inorder_map);
}
