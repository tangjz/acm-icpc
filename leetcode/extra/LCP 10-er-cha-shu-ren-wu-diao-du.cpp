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
    pair<int, double> dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {};
        pair<int, double> lft = dfs(rt -> left), rht = dfs(rt -> right);
        return {lft.first + rht.first + rt -> val, max(max(lft.second, rht.second), (lft.first + rht.first) / 2.0) + rt -> val};
    }
public:
    double minimalExecTime(TreeNode* root) {
        return dfs(root).second;
    }
};
