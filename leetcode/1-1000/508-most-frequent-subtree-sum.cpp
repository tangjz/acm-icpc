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
    int dfs(TreeNode *rt, unordered_map<int, int> &ctr) {
        if(rt == nullptr)
            return 0;
        int ret = rt -> val;
        for(TreeNode *tr: {rt -> left, rt -> right})
            ret += dfs(tr, ctr);
        ++ctr[ret];
        return ret;
    }
public:
    vector<int> findFrequentTreeSum(TreeNode* root) {
        unordered_map<int, int> ctr;
        dfs(root, ctr);
        int best = 0;
        vector<int> ret;
        for(auto &it: ctr) {
            if(it.second > best) {
                best = it.second;
                ret.clear();
            }
            if(it.second == best)
                ret.push_back(it.first);
        }
        return ret;
    }
};
