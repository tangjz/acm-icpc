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
        pair<int, TreeNode *> ret = {0, rt}, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            tmp = dfs(tr);
            ++tmp.first;
            if(ret.first == tmp.first) {
                ret.second = rt;
            } else if(ret.first < tmp.first) {
                ret = tmp;
            }
        }
        return ret;
    }
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        return dfs(root).second;
    }
};
