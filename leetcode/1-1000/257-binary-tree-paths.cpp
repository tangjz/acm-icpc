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
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> ret;
        for(TreeNode *tr: {root -> left, root -> right})
            if(tr != nullptr) {
                vector<string> tmp = binaryTreePaths(tr);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
        if(ret.empty()) {
            ret.push_back(to_string(root -> val));
        } else {
            string pref = to_string(root -> val) + "->";
            for(auto &it: ret)
                it = pref + it;
        }
        return ret;
    }
};
