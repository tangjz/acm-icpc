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
    pair<int, int> dfs(TreeNode *rt) {
        pair<int, int> ret = {}, tmp;
        if(rt == nullptr)
            return ret;
        ret.first += rt -> val;
        for(TreeNode *ch : {rt -> left, rt -> right}) {
            tmp = dfs(ch);
            ret.first += tmp.second;
            ret.second += max(tmp.first, tmp.second);
        }
        return ret;
    }
public:
    int rob(TreeNode* root) {
        pair<int, int> sol = dfs(root);
        return max(sol.first, sol.second);
    }
};
