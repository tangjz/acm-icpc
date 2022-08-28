/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void dfs(TreeNode* &rt, int key) {
        if(rt == nullptr)
            return;
        if((rt -> val) > key) {
            dfs(rt -> left, key);
            return;
        }
        if((rt -> val) < key) {
            dfs(rt -> right, key);
            return;
        }
        if(rt -> left == nullptr) {
            rt = rt -> right;
            return;
        }
        if(rt -> right == nullptr) {
            rt = rt -> left;
            return;
        }
        TreeNode *lft, *rht;
        for(lft = rt -> left, rht = rt -> right; lft -> right != nullptr && rht -> left != nullptr; lft = lft -> right, rht = rht -> left);
        if(lft -> right == nullptr) {
            rt -> val = lft -> val;
            dfs(rt -> left, lft -> val);
        } else {
            rt -> val = rht -> val;
            dfs(rt -> right, rht -> val);
        }
    }
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        dfs(root, key);
        return root;
    }
};
