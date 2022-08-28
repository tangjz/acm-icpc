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
    int dfs(TreeNode *rt, vector<int> &vec) {
        if(rt == NULL)
            return 0;
        int ret = (rt -> val) + dfs(rt -> left, vec) + dfs(rt -> right, vec);
        vec.push_back(ret);
        return ret;
    }
public:
    int maxProduct(TreeNode* root) {
        vector<int> sum;
        dfs(root, sum);
        int all = *max_element(sum.begin(), sum.end());
        typedef long long LL;
        LL ans = 0;
        for(int x : sum)
            ans = max(ans, (LL)x * (all - x));
        return ans % ((int)1e9 + 7);
    }
};
