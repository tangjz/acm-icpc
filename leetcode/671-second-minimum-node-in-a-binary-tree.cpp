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
    pair<int, int> dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {-1, -1};
        vector<int> cand = {rt -> val};
        pair<int, int> ret;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            ret = dfs(tr);
            if(ret.first != -1)
                cand.push_back(ret.first);
            if(ret.second != -1)
                cand.push_back(ret.second);
        }
        sort(cand.begin(), cand.end());
        cand.erase(unique(cand.begin(), cand.end()), cand.end());
        ret.first = cand[0];
        ret.second = cand.size() > 1 ? cand[1] : -1;
        return ret;
    }
public:
    int findSecondMinimumValue(TreeNode* root) {
        return dfs(root).second;
    }
};
