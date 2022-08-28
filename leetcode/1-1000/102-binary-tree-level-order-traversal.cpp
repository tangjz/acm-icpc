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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int> > ret = {{}};
        vector<vector<TreeNode *> > info = {{}};
        if(root != nullptr) {
            ret.back().push_back(root -> val);
            info.back().push_back(root);
        }
        while(!info.back().empty()) {
            vector<int> vals;
            vector<TreeNode *> adt;
            for(TreeNode *rt: info.back())
                for(TreeNode *tr: {rt -> left, rt -> right})
                    if(tr != nullptr) {
                        adt.push_back(tr);
                        vals.push_back(tr -> val);
                    }
            ret.push_back(vals);
            info.push_back(adt);
        }
        ret.pop_back();
        return ret;
    }
};
