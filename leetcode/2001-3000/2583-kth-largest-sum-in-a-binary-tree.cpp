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
    typedef long long LL;
    void dfs(TreeNode *rt, int dep, vector<LL> &sum) {
        if(rt == nullptr)
            return;
        if(dep == sum.size())
            sum.push_back(0);
        sum[dep] += rt -> val;
        dfs(rt -> left, dep + 1, sum);
        dfs(rt -> right, dep + 1, sum);
    }
public:
    long long kthLargestLevelSum(TreeNode* root, int k) {
        vector<LL> sum;
        dfs(root, 0, sum);
        if(sum.size() < k)
            return -1;
        sort(sum.begin(), sum.end());
        return sum[sum.size() - k];
    }
};
