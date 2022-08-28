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
private:
    int dfs(TreeNode *root, int &ans) {
        if(root == NULL)
            return 0;
        int lft = root -> left != NULL ? dfs(root -> left, ans) + 1 : 0;
        int rht = root -> right != NULL ? dfs(root -> right, ans) + 1 : 0;
        ans = max(ans, lft + rht);
        return max(lft, rht);
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
