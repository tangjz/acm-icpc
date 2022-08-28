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
    pair<int, pair<int, int> > dfs(TreeNode *rt, int &ans) {
        if(rt == nullptr)
            return {0, {INT_MAX, INT_MIN}};
        pair<int, pair<int, int> > ret = {1, {rt -> val, rt -> val}}, tmp;
        if(rt -> left != nullptr) {
            tmp = dfs(rt -> left, ans);
            if(tmp.first && tmp.second.second < ret.second.first) {
                ret.first += tmp.first;
            } else {
                ret.first = 0;
            }
            ret.second.first = min(ret.second.first, tmp.second.first);
            ret.second.second = max(ret.second.second, tmp.second.second);
        }
        if(rt -> right != nullptr) {
            tmp = dfs(rt -> right, ans);
            if(ret.first && tmp.first && tmp.second.first > ret.second.second) {
                ret.first += tmp.first;
            } else {
                ret.first = 0;
            }
            ret.second.first = min(ret.second.first, tmp.second.first);
            ret.second.second = max(ret.second.second, tmp.second.second);
        }
        // printf("%d %d %d\n", ret.first, ret.second.first, ret.second.second);
        ans = max(ans, ret.first);
        return ret;
    }
public:
    int largestBSTSubtree(TreeNode* root) {
        int ans = 0;
        dfs(root, ans);
        return ans;
    }
};
