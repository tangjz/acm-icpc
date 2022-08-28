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
    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = preorder.size(), p = 0, q = 0;
        function<TreeNode *()> dfs = [&]() {
            TreeNode *ret = new TreeNode(preorder[p++]);
            if(ret -> val != postorder[q])
                ret -> left = dfs();
            if(ret -> val != postorder[q])
                ret -> right = dfs();
            assert(ret -> val == postorder[q++]);
            return ret;
        };
        return dfs();
    }
};
