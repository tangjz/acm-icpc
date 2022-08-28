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
    TreeNode *dfs(int L, int R, string &s, vector<int> &pL) {
        if(L > R)
            return nullptr;
        if(s[R] != ')')
            return new TreeNode(stoi(s.substr(L, R - L + 1)));
        int u, v = pL[R];
        if(s[v - 1] != ')') {
            u = v;
            v = R + 1;
        } else {
            u = pL[v - 1];
        }
        return new TreeNode(stoi(s.substr(L, u - L)), dfs(u + 1, v - 2, s, pL), dfs(v + 1, R - 1, s, pL));
    }
public:
    TreeNode* str2tree(string s) {
        int n = s.size();
        stack<int> stk;
        vector<int> pL(n, -1);
        for(int i = 0; i < n; ++i)
            if(s[i] == '(') {
                stk.push(i);
            } else if(s[i] == ')') {
                pL[i] = stk.top();
                stk.pop();
            }
        return dfs(0, n - 1, s, pL);
    }
};
