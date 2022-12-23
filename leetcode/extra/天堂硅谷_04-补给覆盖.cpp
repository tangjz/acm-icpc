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
    pair<int, int> dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {};
        pair<int, int> ret = {-1, 0}, tmp;
        bool need = 0;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            tmp = dfs(tr);
            if(tmp.first == 2)
                need = 1;
            ret = {max(ret.first, tmp.first - 1), ret.second + tmp.second};
        }
        if(need)
            ++ret.second;
        if(ret.first < 0)
            ret.first = 2;
        return ret;
    }
public:
    int minSupplyStationNumber(TreeNode* root) {
        pair<int, int> ret = dfs(root);
        return ret.second + (ret.first == 2);
    }
};
