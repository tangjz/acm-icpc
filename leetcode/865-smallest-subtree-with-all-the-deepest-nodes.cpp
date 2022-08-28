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
    pair<int, TreeNode *> dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {};
        pair<int, TreeNode *> lft = dfs(rt -> left), rht = dfs(rt -> right);
        if(lft.first < rht.first)
            return {rht.first + 1, rht.second};
        if(lft.first > rht.first)
            return {lft.first + 1, lft.second};
        return {lft.first + 1, rt};
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs(root).second;
    }
};
