/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    vector<int> dfs(TreeNode *rt, int upp) {
        if(rt == nullptr)
            return {0};
        vector<int> ret = {0, rt -> val};
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            if(tr == nullptr)
                continue;
            vector<int> tmp = dfs(tr, upp);
            ret.front() += *max_element(tmp.begin(), tmp.end());
            int sz = ret.size();
            ret.resize(min(sz + (int)tmp.size() - 1, upp + 1));
            for(int i = ret.size() - 1; i > 0; --i)
                for(int j = 0; j < tmp.size() && j < i; ++j)
                    ret[i] = max(ret[i], ret[i - j] + tmp[j]);
        }
        return ret;
    }
public:
    int maxValue(TreeNode* root, int k) {
        vector<int> ret = dfs(root, k);
        return *max_element(ret.begin(), ret.end());
    }
};
