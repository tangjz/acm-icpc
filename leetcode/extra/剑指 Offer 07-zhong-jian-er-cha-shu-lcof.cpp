/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    TreeNode *dfs(vector<int> const &pre, int pL, int pR, vector<int> const &in, int iL, int iR, unordered_map<int, int> &pos) {
        if(pL > pR)
            return nullptr;
        int val = pre[pL], iM = pos[val], ofs = iM - iL;
        return new TreeNode(val, dfs(pre, pL + 1, pL + ofs, in, iL, iM - 1, pos), dfs(pre, pL + ofs + 1, pR, in, iM + 1, iR, pos));
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = inorder.size();
        unordered_map<int, int> pos;
        for(int i = 0; i < n; ++i)
            pos[inorder[i]] = i;
        return dfs(preorder, 0, n - 1, inorder, 0, n - 1, pos);
    }
};
