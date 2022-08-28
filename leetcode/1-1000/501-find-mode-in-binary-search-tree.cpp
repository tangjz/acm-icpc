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
    void dfs(TreeNode *rt, unordered_map<int, int> &ctr) {
        if(rt == nullptr)
            return;
        ++ctr[rt -> val];
        dfs(rt -> left, ctr);
        dfs(rt -> right, ctr);
    }
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> ctr;
        dfs(root, ctr);
        int cnt = 0;
        vector<int> ret;
        for(auto &it: ctr) {
            if(cnt < it.second) {
                cnt = it.second;
                ret.clear();
            }
            if(cnt == it.second)
                ret.push_back(it.first);
        }
        return ret;
    }
};
