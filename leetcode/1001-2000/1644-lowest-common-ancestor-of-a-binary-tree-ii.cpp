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
    pair<int, TreeNode *> dfs(TreeNode *rt, TreeNode *p, TreeNode *q) {
        pair<int, TreeNode *> ret = {0, nullptr};
        if(rt == nullptr)
            return ret;
        if(rt == p) {
            ret.first |= 1;
            ret.second = rt;
        }
        if(rt == q) {
            ret.first |= 2;
            ret.second = rt;
        }
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            pair<int, TreeNode *> tmp = dfs(tr, p, q);
            ret.first |= tmp.first;
            if(tmp.second != nullptr)
                ret.second = ret.second != nullptr ? rt : tmp.second;
        }
        return ret;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pair<int, TreeNode *> ret = dfs(root, p, q);
        return ret.first == 3 ? ret.second : nullptr;
    }
};
