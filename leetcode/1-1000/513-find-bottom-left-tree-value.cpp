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
        pair<int, int> ret = {0, rt -> val}, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            tmp = dfs(tr);
            ++tmp.first;
            if(tmp.first > ret.first)
                ret = tmp;
        }
        return ret;
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        return dfs(root).second;
    }
};
