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
    void dfs(TreeNode *rt, TreeNode *par, vector<vector<int> > &e) {
        if(rt == nullptr)
            return;
        if(par != nullptr) {
            int upp = max(rt -> val, par -> val);
            if(upp >= (int)e.size())
                e.resize(upp + 1);
            e[rt -> val].push_back(par -> val);
            e[par -> val].push_back(rt -> val);
        }
        dfs(rt -> left, rt, e);
        dfs(rt -> right, rt, e);
    }
public:
    int navigation(TreeNode* root) {
        vector<vector<int> > e;
        dfs(root, nullptr, e);
        int ans = 0, n = e.size() - 1;
        for(int i = 1; i <= n; ++i)
            if(e[i].size() == 1)
                ++ans;
        if(ans == 2)
            return 1;
        unordered_set<int> adt;
        for(int i = 1; i <= n; ++i) {
            if(e[i].size() != 1)
                continue;
            int j = e[i].back(), k = i;
            while(e[j].size() == 2) {
                int p = e[j].back() == k ? e[j].front() : e[j].back();
                k = j;
                j = p;
            }
            if(adt.insert(j).second)
                --ans;
        }
        return ans;
    }
};
