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
    void dfs(TreeNode *rt, int dep, vector<int> &seq, vector<int> &in, vector<int> &out) {
        if(rt == nullptr)
            return;
        seq.push_back(dep);
        int &val = rt -> val;
        while(val >= in.size()) {
            in.push_back(-1);
            out.push_back(-1);
        }
        in[val] = seq.size() - 1;
        dfs(rt -> left, dep + 1, seq, in, out);
        dfs(rt -> right, dep + 1, seq, in, out);
        out[val] = seq.size() - 1;
    }
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        vector<int> seq, in, out;
        dfs(root, 0, seq, in, out);
        int n = seq.size();
        vector<int> pre(n), suf(n);
        for(int i = 0; i < n; ++i) {
            pre[i] = seq[i];
            if(i > 0)
                pre[i] = max(pre[i], pre[i - 1]);
        }
        for(int i = n - 1; i >= 0; --i) {
            suf[i] = seq[i];
            if(i + 1 < n)
                suf[i] = max(suf[i], suf[i + 1]);
        }
        vector<int> ret;
        for(int x: queries) {
            int L = in[x], R = out[x], ans = 0;
            if(L != -1) {
                if(L > 0)
                    ans = max(ans, pre[L - 1]);
                if(R + 1 < n)
                    ans = max(ans, suf[R + 1]);
            } else {
                ans = pre[n - 1];
            }
            ret.push_back(ans);
        }
        return ret;
    }
};
