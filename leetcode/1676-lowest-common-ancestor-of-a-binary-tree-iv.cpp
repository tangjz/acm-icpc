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
    int dfs(TreeNode *rt, unordered_set<int> &sp, TreeNode* &ret) {
        if(rt == nullptr)
            return 0;
        int cnt = sp.count(rt -> val) + dfs(rt -> left, sp, ret) + dfs(rt -> right, sp, ret);
        if(ret == nullptr && cnt == sp.size())
            ret = rt;
        return cnt;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        TreeNode *ret = nullptr;
        unordered_set<int> sp;
        for(TreeNode *tr: nodes)
            sp.insert(tr -> val);
        dfs(root, sp, ret);
        return ret;
    }
};
