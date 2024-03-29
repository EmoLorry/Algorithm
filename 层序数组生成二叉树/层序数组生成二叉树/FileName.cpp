#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 根据带有null的数组生成二叉树
TreeNode* arrayToTree(const vector<string>& arr) {
    if (arr.empty() || arr[0] == "null") return nullptr;

    // 创建根节点
    TreeNode* root = new TreeNode(stoi(arr[0]));
    queue<TreeNode*> q;
    q.push(root);

    // 从数组的第二个元素开始构建二叉树
    int i = 1;
    while (i < arr.size()) {
        TreeNode* parent = q.front();
        q.pop();

        // 创建左子节点
        if (arr[i] != "null") {
            parent->left = new TreeNode(stoi(arr[i]));
            q.push(parent->left);
        }
        i++;

        // 创建右子节点
        if (i < arr.size() && arr[i] != "null") {
            parent->right = new TreeNode(stoi(arr[i]));
            q.push(parent->right);
        }
        i++;
    }

    return root;
}

// 递归前序遍历二叉树
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

int main() {
    vector<string> arr = { "1", "2", "3", "null", "5" }; // 示例数组，null表示空节点
    TreeNode* root = arrayToTree(arr);

    cout << "前序遍历结果: ";
    preorder(root);
    cout << endl;

    return 0;
}
