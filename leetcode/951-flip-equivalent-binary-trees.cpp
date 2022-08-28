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
    int dfs(TreeNode *rt, map<vector<int>, int> &Hash) {
        if(rt == nullptr)
            return -1;
        vector<int> rep = {rt -> val, dfs(rt -> left, Hash), dfs(rt -> right, Hash)};
        if(rep[1] > rep[2])
            swap(rep[1], rep[2]);
        auto it = Hash.find(rep);
        if(it != Hash.end())
            return it -> second;
        int tot = Hash.size();
        Hash.insert({rep, tot});
        return tot;
    }
public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        map<vector<int>, int> Hash;
        int u = dfs(root1, Hash);
        int v = dfs(root2, Hash);
        return u == v;
    }
};
