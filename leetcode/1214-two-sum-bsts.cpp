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
    vector<int> dfs(TreeNode *rt) {
        if(rt == nullptr)
            return {};
        vector<int> ret = {rt -> val}, tmp;
        for(TreeNode *tr: {rt -> left, rt -> right}) {
            tmp = move(dfs(tr));
            ret.insert(ret.end(), tmp.begin(), tmp.end());
        }
        return ret;
    }
public:
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        vector<int> a = dfs(root1), b = dfs(root2);
        unordered_set<int> Hash(a.begin(), a.end());
        for(int x: b)
            if(Hash.count(target - x))
                return 1;
        return 0;
    }
};
