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
public:
    int minCameraCover(TreeNode* root) {
        int ans = 0;
        vector<TreeNode *> que;
        vector<int> par;
        que.push_back(root);
        par.push_back(-1);
        for(int i = 0; i < (int)que.size(); ++i) {
            TreeNode *rt = que[i];
            for(TreeNode *tr: {rt -> left, rt -> right})
                if(tr != nullptr) {
                    que.push_back(tr);
                    par.push_back(i);
                }
        }
        for(int i = (int)que.size() - 1; i >= 0; --i) {
            TreeNode *rt = que[i];
            bool skip = rt -> val;
            if(par[i] >= 0)
                skip |= que[par[i]] -> val;
            for(TreeNode *tr: {rt -> left, rt -> right})
                skip |= tr != nullptr && tr -> val;
            if(!skip) {
                ++ans;
                (par[i] >= 0 ? que[par[i]] : rt) -> val = 1;
            }
        }
        return ans;
    }
};
