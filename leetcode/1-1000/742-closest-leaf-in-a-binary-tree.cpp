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
    void dfs(TreeNode *rt, unordered_map<int, int> &par, unordered_map<int, vector<int> > &e) {
        if(rt == nullptr)
            return;
        for(TreeNode *tr: {rt -> left, rt -> right})
            if(tr != nullptr) {
                par[tr -> val] = rt -> val;
                e[rt -> val].push_back(tr -> val);
                e[tr -> val].push_back(rt -> val);
                dfs(tr, par, e);
            }
    }
public:
    int findClosestLeaf(TreeNode* root, int k) {
        unordered_map<int, int> par;
        unordered_map<int, vector<int> > e;
        par[root -> val] = -1;
        dfs(root, par, e);
        queue<pair<int, int> > que;
        if(!e[k].size() || e[k].size() == 1 && par[k] == e[k].back())
            return k;
        que.push({k, -1});
        while(!que.empty()) {
            int u, p;
            tie(u, p) = que.front();
            que.pop();
            for(int v: e[u]) {
                if(v == p)
                    continue;
                if(e[v].size() == 1 && par[v] == e[v].back())
                    return v;
                que.push({v, u});
            }
        }
        return -1;
    }
};
