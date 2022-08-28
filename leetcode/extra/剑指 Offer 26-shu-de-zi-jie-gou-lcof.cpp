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
    bool dfs(TreeNode *A, TreeNode *B) {
        return B == nullptr ? true : (A == nullptr ? false : (A -> val == B -> val && dfs(A -> left, B -> left) && dfs(A -> right, B -> right)));
    }
public:
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        return A == nullptr || B == nullptr ? false : (isSubStructure(A -> left, B) || isSubStructure(A -> right, B) || dfs(A, B));
    }
};
