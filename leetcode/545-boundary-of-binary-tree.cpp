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
    void dfs(TreeNode *rt, bool isLeft, bool isRight, vector<int> &pL, vector<int> &pM, vector<int> &pR) {
        if(rt == nullptr)
            return;
        if(rt -> left == nullptr && rt -> right == nullptr) {
            pM.push_back(rt -> val);
            return;
        }
        if(isLeft)
            pL.push_back(rt -> val);
        if(isRight)
            pR.push_back(rt -> val);
        dfs(rt -> left, isLeft, rt -> right == nullptr ? isRight : 0, pL, pM, pR);
        dfs(rt -> right, rt -> left == nullptr ? isLeft : 0, isRight, pL, pM, pR);
    }
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        vector<int> pL, pM, pR;
        pL.push_back(root -> val);
        dfs(root -> left, true, false, pL, pM, pR);
        dfs(root -> right, false, true, pL, pM, pR);
        pL.insert(pL.end(), pM.begin(), pM.end());
        reverse(pR.begin(), pR.end());
        pL.insert(pL.end(), pR.begin(), pR.end());
        return pL;
    }
};
