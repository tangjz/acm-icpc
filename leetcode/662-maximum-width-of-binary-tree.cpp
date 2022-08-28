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
    int mx;
    vector<pair<TreeNode *, unsigned> > lft, rht;
    void dfs(int dep, TreeNode *rt, unsigned idx) {
        if(rt == NULL)
            return;
        for( ; mx <= dep; ++mx) {
            lft.push_back({nullptr, 0});
            rht.push_back({nullptr, 0});
        }
        rht[dep] = {rt, idx};
        if(lft[dep].first == nullptr)
            lft[dep] = rht[dep];
        dfs(dep + 1, rt -> left, idx << 1);
        dfs(dep + 1, rt -> right, idx << 1 | 1);
    }
public:
    int widthOfBinaryTree(TreeNode* root) {
        mx = 0;
        vector<pair<TreeNode *, unsigned> >().swap(lft);
        vector<pair<TreeNode *, unsigned> >().swap(rht);
        dfs(0, root, 0);
        unsigned ret = 0;
        for(int i = 0; i < mx; ++i)
            ret = max(ret, rht[i].second - lft[i].second + 1);
        return ret;
    }
};
