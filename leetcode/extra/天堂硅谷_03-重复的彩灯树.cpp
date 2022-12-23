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
    vector<TreeNode*> lightDistribution(TreeNode* root) {
        map<pair<int, pair<int, int> >, int> Hash;
        vector<pair<TreeNode*, int> > ctr;
        function<int(TreeNode *)> dfs = [&](TreeNode *rt) {
            if(rt == nullptr)
                return -1;
            pair<int, int> sub = {dfs(rt -> left), dfs(rt -> right)};
            auto ret = Hash.insert({{rt -> val, sub}, Hash.size()});
            if(ret.second)
                ctr.push_back({rt, 0});
            int idx = ret.first -> second;
            ++ctr[idx].second;
            return idx;
        };
        dfs(root);
        vector<TreeNode*> ret;
        for(auto &it: ctr)
            if(it.second > 1)
                ret.push_back(it.first);
        return ret;
    }
};
