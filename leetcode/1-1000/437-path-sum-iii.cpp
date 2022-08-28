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
    typedef long long LL;
    int dfs(TreeNode *rt, LL pre, LL sum, unordered_map<LL, int> &ctr) {
        if(rt == NULL)
            return 0;
        pre += rt -> val;
        int ret = 0;
        auto it = ctr.find(pre - sum);
        if(it != ctr.end())
            ret += it -> second;
        ++ctr[pre];
        for(TreeNode *ch : {rt -> left, rt -> right})
            ret += dfs(ch, pre, sum, ctr);
        if(!(--ctr[pre]))
            ctr.erase(pre);
        return ret;
    }
public:
    int pathSum(TreeNode* root, int sum) {
        unordered_map<LL, int> ctr;
        ++ctr[0];
        return dfs(root, 0, sum, ctr);
    }
};
