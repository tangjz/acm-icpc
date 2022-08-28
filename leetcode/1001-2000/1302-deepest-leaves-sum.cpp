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
    pair<int, int> dfs(TreeNode *rt, int dep) {
        if(rt == NULL)
            return {-1, 0};
        pair<int, int> ret = {dep, rt -> val};
        for(TreeNode *ch : {rt -> left, rt -> right}) {
            pair<int, int> tmp = dfs(ch, dep + 1);
            if(tmp.first > ret.first)
                ret = {tmp.first, 0};
            if(tmp.first == ret.first)
                ret.second += tmp.second;
        }
        return ret;
    }
public:
    int deepestLeavesSum(TreeNode* root) {
        return dfs(root, 0).second;
    }
};
