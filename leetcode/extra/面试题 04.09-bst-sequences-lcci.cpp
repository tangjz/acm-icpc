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
public:
    vector<vector<int>> BSTSequences(TreeNode* root) {
        vector<int> pre;
        for( ; root != nullptr && (root -> left == nullptr || root -> right == nullptr); root = root -> left != nullptr ? root -> left : root -> right)
        pre.push_back(root -> val);
        if(root == nullptr)
            return {pre};
        pre.push_back(root -> val);
        vector<vector<int> > ret, lft = BSTSequences(root -> left), rht = BSTSequences(root -> right);
        int cL = lft[0].size(), cR = rht[0].size(), sz = pre.size() + cL + cR;
        vector<int> path(cL + cR);
        function<void(int, int)> dfs = [&](int rL, int rR) {
            if(!rL || !rR) {
                for( ; rL > 0; --rL, path[rL] = rL);
                for( ; rR > 0; --rR, path[rR] = cL + rR);
                for(auto &it: lft)
                    for(auto &jt: rht) {
                        ret.push_back(pre);
                        ret.back().reserve(sz);
                        for(int &idx: path)
                            ret.back().push_back(idx < cL ? it[idx] : jt[idx - cL]);
                    }
                return;
            }
            path[rL + rR - 1] = rL - 1;
            dfs(rL - 1, rR);
            path[rL + rR - 1] = cL + rR - 1;
            dfs(rL, rR - 1);
        };
        dfs(cL, cR);
        return ret;
    }
};
