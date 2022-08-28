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
    void dfs(TreeNode *rt, set<int> &sp) {
        if(rt != nullptr) {
            sp.insert(rt -> val);
            dfs(rt -> left, sp);
            dfs(rt -> right, sp);
        }
    }
public:
    int minDiffInBST(TreeNode* root) {
        set<int> sp;
        dfs(root, sp);
        int ans = INT_MAX, las = INT_MIN;
        for(int x: sp) {
            if(las != INT_MIN)
                ans = min(ans, x - las);
            las = x;
        }
        return ans;
    }
};
