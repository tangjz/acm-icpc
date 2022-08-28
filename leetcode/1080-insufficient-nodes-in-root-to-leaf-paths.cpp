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
    TreeNode *dfs(TreeNode *rt, int lim, int cur, int &ret) {
        if(rt == nullptr)
            return nullptr;
        if(rt -> left == nullptr && rt -> right == nullptr) {
            ret = rt -> val;
            return cur + ret >= lim ? rt : nullptr;
        }
        for(TreeNode **ptr: {&(rt -> left), &(rt -> right)}) {
            int tmp = INT_MIN;
            *ptr = dfs(*ptr, lim, cur + (rt -> val), tmp);
            if(tmp > INT_MIN)
                ret = max(ret, rt -> val + tmp);
        }
        return cur + ret >= lim ? rt : nullptr;
    }
public:
    TreeNode* sufficientSubset(TreeNode* root, int limit) {
        int upp = INT_MIN;
        return dfs(root, limit, 0, upp);
    }
};
