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
    void dfs(TreeNode *rt, int dep, int L, int R, int &mx, vector<vector<int> > &seq) {
        if(rt == nullptr)
            return;
        mx = max(mx, dep + 1);
        int M = (L + R) / 2;
        seq.push_back({dep, M, rt -> val});
        dfs(rt -> left, dep + 1, L, M - 1, mx, seq);
        dfs(rt -> right, dep + 1, M + 1, R, mx, seq);
    }
public:
    vector<vector<string>> printTree(TreeNode* root) {
        static const int maxd = 10;
        int mx = 0;
        vector<vector<int> > seq;
        dfs(root, 0, 0, (1 << maxd) - 1, mx, seq);
        vector<vector<string> > ret(mx, vector<string>((1 << mx) - 1));
        for(auto &it: seq)
            ret[it[0]][it[1] >> (maxd - mx)] = to_string(it[2]);
        return ret;
    }
};
