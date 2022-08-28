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
    bool isCompleteTree(TreeNode* root) {
        bool stp = 0;
        vector<TreeNode *> que;
        que.push_back(root);
        for(int i = 0; i < (int)que.size(); ++i) {
            TreeNode *rt = que[i];
            for(TreeNode *tr: {rt -> left, rt -> right}) {
                if(tr == nullptr) {
                    stp = 1;
                    continue;
                }
                if(stp)
                    return 0;
                que.push_back(tr);
            }
        }
        return 1;
    }
};
