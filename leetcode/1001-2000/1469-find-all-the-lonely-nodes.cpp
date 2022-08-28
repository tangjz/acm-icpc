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
    void dfs(TreeNode *rt, vector<int> &ret) {
        if(rt == nullptr)
            return;
        int val = -1;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            val = val == -1 ? tr -> val : -1;
            dfs(tr, ret);
        }
        if(val != -1)
            ret.push_back(val);
    }
public:
    vector<int> getLonelyNodes(TreeNode* root) {
        vector<int> ret;
        dfs(root, ret);
        return ret;
    }
};
