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
    TreeNode *dfs(TreeNode *rt, unordered_set<int> const &vals, vector<TreeNode *> &seq) {
        if(rt == nullptr)
            return nullptr;
        bool found = vals.count(rt -> val);
        for(TreeNode **ptr: {&(rt -> left), &(rt -> right)}) {
            *ptr = dfs(*ptr, vals, seq);
            if(*ptr != nullptr && found)
                seq.push_back(*ptr);
        }
        return found ? nullptr : rt;
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> vals;
        for(int x: to_delete)
            vals.insert(x);
        vector<TreeNode *> seq;
        root = dfs(root, vals, seq);
        if(root != nullptr)
            seq.push_back(root);
        return seq;
    }
};
