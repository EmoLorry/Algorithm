#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// �������ڵ㶨��
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ���ݴ���null���������ɶ�����
TreeNode* arrayToTree(const vector<string>& arr) {
    if (arr.empty() || arr[0] == "null") return nullptr;

    // �������ڵ�
    TreeNode* root = new TreeNode(stoi(arr[0]));
    queue<TreeNode*> q;
    q.push(root);

    // ������ĵڶ���Ԫ�ؿ�ʼ����������
    int i = 1;
    while (i < arr.size()) {
        TreeNode* parent = q.front();
        q.pop();

        // �������ӽڵ�
        if (arr[i] != "null") {
            parent->left = new TreeNode(stoi(arr[i]));
            q.push(parent->left);
        }
        i++;

        // �������ӽڵ�
        if (i < arr.size() && arr[i] != "null") {
            parent->right = new TreeNode(stoi(arr[i]));
            q.push(parent->right);
        }
        i++;
    }

    return root;
}

// �ݹ�ǰ�����������
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    vector<string> arr = { "1", "2", "3", "null", "5" }; // ʾ�����飬null��ʾ�սڵ�
    TreeNode* root = arrayToTree(arr);

    cout << "ǰ��������: ";
    preorder(root);
    cout << endl;

    return 0;
}
