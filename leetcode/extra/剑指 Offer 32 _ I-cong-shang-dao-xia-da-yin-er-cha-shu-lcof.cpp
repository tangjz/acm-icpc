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
public:
    vector<int> levelOrder(TreeNode* root) {
        vector<int> ret = {};
        queue<TreeNode *> info;
        if(root != nullptr) {
            ret.push_back(root -> val);
            info.push(root);
        }
        while(!info.empty()) {
            TreeNode *rt = info.front();
            info.pop();
            for(TreeNode *tr: {rt -> left, rt -> right})
                if(tr != nullptr) {
                    ret.push_back(tr -> val);
                    info.push(tr);
                }
        }
        return ret;
    }
};
