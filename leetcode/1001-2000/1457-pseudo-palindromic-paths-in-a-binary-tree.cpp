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
    bool isLeaf(TreeNode *rt) {
        return rt != nullptr && (rt -> left) == nullptr && (rt -> right) == nullptr;
    }
    bool check(int msk) {
        return !(msk & (msk - 1));
    }
    int dfs(TreeNode *rt, int msk) {
        if(rt == nullptr)
            return 0;
        msk ^= 1 << ((rt -> val) - 1);
        int ret = isLeaf(rt) && check(msk);
        ret += dfs(rt -> left, msk);
        ret += dfs(rt -> right, msk);
        return ret;
    }
public:
    int pseudoPalindromicPaths (TreeNode* root) {
        return dfs(root, 0);
    }
};
