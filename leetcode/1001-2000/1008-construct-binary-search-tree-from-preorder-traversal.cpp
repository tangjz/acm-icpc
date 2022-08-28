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
    TreeNode *dfs(vector<int> const &seq, int L, int R) {
        if(L > R)
            return nullptr;
        int M = L + 1;
        for( ; M <= R && seq[L] > seq[M]; ++M);
        return new TreeNode(seq[L], dfs(seq, L + 1, M - 1), dfs(seq, M, R));
    }
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int n = preorder.size();
        return dfs(preorder, 0, n - 1);
    }
};
