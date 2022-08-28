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
    pair<int, int> dfs(TreeNode *rt) {
        int typ = rt -> val;
        if(typ < 2)
            return {typ, !typ};
        if(typ == 5) {
            pair<int, int> tmp = rt -> left != nullptr ? dfs(rt -> left) : dfs(rt -> right);
            return {tmp.second, tmp.first};
        }
        pair<int, int> lft = dfs(rt -> left), rht = dfs(rt -> right);
        int cost[2][2] = {{lft.first, lft.second}, {rht.first, rht.second}}, ret[2] = {INT_MAX, INT_MAX};
        for(int i = 0; i < 2; ++i)
            for(int j = 0; j < 2; ++j) {
                int k = typ == 2 ? (i | j) : (typ == 3 ? (i & j) : (i ^ j));
                ret[k] = min(ret[k], cost[0][i] + cost[1][j]);
            }
        return {ret[0], ret[1]};
    }
public:
    int minimumFlips(TreeNode* root, bool result) {
        pair<int, int> ret = dfs(root);
        return result ? ret.second : ret.first;
    }
};
