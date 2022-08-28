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
    TreeNode *dfs(int cnt, int pL, int qL, vector<int> &mid, vector<int> &post, unordered_map<int, int> &pos) {
        if(cnt <= 0)
            return NULL;
        int x = post[qL + cnt - 1], idx = pos[x], cL = idx - pL, cR = cnt - cL - 1;
        return new TreeNode(x, dfs(cL, pL, qL, mid, post, pos), dfs(cR, idx + 1, qL + cL, mid, post, pos));
    }
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        unordered_map<int, int> pos;
        int idx = 0;
        for(int x : inorder)
            pos.insert({x, idx++});
        return dfs(idx, 0, 0, inorder, postorder, pos);
    }
};
