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
    pair<int, int> dfs(TreeNode *rt, int p, int q) {
        pair<int, int> ret = {0, 0};
        if(rt == nullptr)
            return ret;
        if(rt -> val == p)
            ret.first |= 1;
        if(rt -> val == q)
            ret.first |= 2;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            pair<int, int> tmp = dfs(tr, p, q);
            ret.first |= tmp.first;
            ret.second += tmp.second;
        }
        if(ret.first > 0 && ret.first < 3)
            ++ret.second;
        return ret;
    }
public:
    int findDistance(TreeNode* root, int p, int q) {
        return dfs(root, p, q).second;
    }
};
