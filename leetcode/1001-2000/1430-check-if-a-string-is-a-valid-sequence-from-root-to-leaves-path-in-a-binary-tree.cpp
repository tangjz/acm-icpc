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
    bool dfs(TreeNode *rt, vector<int> &arr, int pos) {
        if(rt == nullptr || pos == arr.size() || arr[pos] != rt -> val)
            return 0;
        bool leaf = 1;
        for(TreeNode *tr: {rt -> left, rt -> right})
            if(tr != nullptr) {
                leaf = 0;
                if(dfs(tr, arr, pos + 1))
                    return 1;
            }
        return leaf && pos == arr.size() - 1;
    }
public:
    bool isValidSequence(TreeNode* root, vector<int>& arr) {
        return dfs(root, arr, 0);
    }
};
