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
    void dfs(TreeNode *rt, set<int> &col) {
        if(rt == nullptr)
            return;
        dfs(rt -> left, col);
        dfs(rt -> right, col);
        col.insert(rt -> val);
    }
public:
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
        set<int> col;
        dfs(root, col);
        reverse(ops.begin(), ops.end());
        int cnt = 0;
        for(auto &it: ops) {
            int typ = it[0], L = it[1], R = it[2];
            for(auto jt = col.lower_bound(L); jt != col.end() && *jt <= R; jt = col.erase(jt))
                cnt += typ == 1;
        }
        return cnt;
    }
};
