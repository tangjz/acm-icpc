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
    vector<TreeNode *> dfs(int L, int R) {
        if(L > R)
            return {nullptr};
        vector<TreeNode *> ret = {}, lft, rht;
        for(int i = L; i <= R; ++i) {
            lft = dfs(L, i - 1);
            rht = dfs(i + 1, R);
            for(auto &it: lft)
                for(auto &jt: rht)
                    ret.push_back(new TreeNode(i, it, jt));
        }
        return ret;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        return dfs(1, n);
    }
};
