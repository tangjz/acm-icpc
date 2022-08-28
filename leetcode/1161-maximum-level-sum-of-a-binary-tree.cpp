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
    void dfs(TreeNode *rt, int dep, vector<int> &sum) {
        if(rt == nullptr)
            return;
        if(dep == sum.size())
            sum.push_back(0);
        sum[dep] += rt -> val;
        dfs(rt -> left, dep + 1, sum);
        dfs(rt -> right, dep + 1, sum);
    }
public:
    int maxLevelSum(TreeNode* root) {
        vector<int> sum;
        dfs(root, 0, sum);
        int best = 0;
        for(int i = 1; i < (int)sum.size(); ++i)
            if(sum[i] > sum[best])
                best = i;
        return best + 1;
    }
};
