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
    void dfs1(TreeNode *root, vector<int> &seq) {
        if(root == NULL)
            return;
        dfs1(root -> left, seq);
        seq.push_back(root -> val);
        dfs1(root -> right, seq);
    }
    TreeNode *dfs2(vector<int> &seq, int L, int R) {
        if(L > R)
            return NULL;
        int M = (L + R) >> 1;
        TreeNode *lft = dfs2(seq, L, M - 1), *rht = dfs2(seq, M + 1, R);
        return new TreeNode(seq[M], lft, rht);
    }
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<int> seq;
        dfs1(root, seq);
        return dfs2(seq, 0, (int)seq.size() - 1);
    }
};
