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
    void dfs1(TreeNode *rt, int dep, vector<int> &sum) {
        if(rt == nullptr)
            return;
        if(dep == sum.size())
            sum.push_back(0);
        sum[dep] += rt -> val;
        dfs1(rt -> left, dep + 1, sum);
        dfs1(rt -> right, dep + 1, sum);
    }
    void dfs2(TreeNode *rt, int dep, vector<int> &sum) {
        if(rt == nullptr)
            return;
        int rem = dep + 1 < sum.size() ? sum[dep + 1] : 0;
        if(rt -> left)
            rem -= rt -> left -> val;
        if(rt -> right)
            rem -= rt -> right -> val;
        if(rt -> left)
            rt -> left -> val = rem;
        if(rt -> right)
            rt -> right -> val = rem;
        dfs2(rt -> left, dep + 1, sum);
        dfs2(rt -> right, dep + 1, sum);
    }
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        vector<int> sum;
        dfs1(root, 0, sum);
        root -> val = 0;
        dfs2(root, 0, sum);
        return root;
    }
};
