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
    int dfs(TreeNode *rt, unordered_set<int> &Hash) {
        int ret = rt -> val;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            int adt = dfs(tr, Hash);
            Hash.insert(adt);
            ret += adt;
        }
        return ret;
    }
public:
    bool checkEqualTree(TreeNode* root) {
        unordered_set<int> Hash;
        int sum = dfs(root, Hash);
        return !(sum & 1) && Hash.count(sum >> 1);
    }
};
