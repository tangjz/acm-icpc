/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    void dfs(TreeNode* rt, unordered_set<int> &sp) {
        if(rt == nullptr)
            return;
        sp.insert(rt -> val);
        dfs(rt -> left, sp);
        dfs(rt -> right, sp);
    }
public:
    int numColor(TreeNode* root) {
        unordered_set<int> sp;
        dfs(root, sp);
        return sp.size();
    }
};
