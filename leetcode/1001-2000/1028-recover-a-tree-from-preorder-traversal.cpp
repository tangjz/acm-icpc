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
    TreeNode* recoverFromPreorder(string seq) {
        int n = seq.size(), pos = 0;
        TreeNode *rt = new TreeNode();
        for( ; pos < n && seq[pos] != '-'; rt -> val = (rt -> val) * 10 + (seq[pos++] - '0'));
        stack<TreeNode *> stk;
        stk.push(rt);
        while(pos < n) {
            int dep = 0;
            for( ; pos < n && seq[pos] == '-'; ++dep, ++pos);
            TreeNode *tp = new TreeNode();
            for( ; pos < n && seq[pos] != '-'; tp -> val = (tp -> val) * 10 + (seq[pos++] - '0'));
            while(stk.size() > dep)
                stk.pop();
            TreeNode *up = stk.top();
            if(up -> left == nullptr) {
                up -> left = tp;
            } else {
                up -> right = tp;
            }
            stk.push(tp);
        }
        return rt;
    }
};
