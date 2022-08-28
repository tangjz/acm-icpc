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
    void dfs(TreeNode *rt, vector<pair<double, int> > &cand, double &target) {
        if(rt == nullptr)
            return;
        cand.push_back({abs(rt -> val - target), rt -> val});
        dfs(rt -> left, cand, target);
        dfs(rt -> right, cand, target);
    }
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        vector<pair<double, int> > cand;
        dfs(root, cand, target);
        nth_element(cand.begin(), cand.begin() + k, cand.end());
        vector<int> ret(k);
        for(int i = 0; i < k; ++i)
            ret[i] = cand[i].second;
        return ret;
    }
};
