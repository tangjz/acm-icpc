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
        dfs(rt -> left, ret);
        ret.push_back(rt -> val);
        dfs(rt -> right, ret);
    }
public:
    bool findTarget(TreeNode* root, int k) {
        vector<int> ret;
        dfs(root, ret);
        int n = ret.size();
        for(int i = 0, j = n - 1; i < j; ++i) {
            for( ; i < j && ret[i] + ret[j] > k; --j);
            if(i < j && ret[i] + ret[j] == k)
                return true;
        }
        return false;
    }
};
