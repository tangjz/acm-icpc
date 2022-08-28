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
    int tot;
    map<vector<int>, int> pos;
    vector<vector<TreeNode *> > cand;
    
    int dfs(TreeNode *rt) {
        if(rt == nullptr)
            return 0;
        vector<int> rep = {rt -> val, dfs(rt -> left), dfs(rt -> right)};
        auto it = pos.find(rep);
        int idx = it == pos.end() ? (pos[rep] = ++tot) : it -> second;
        while(idx >= cand.size())
            cand.push_back({});
        if(cand[idx].size() < 2)
            cand[idx].push_back(rt);
        return idx;
    }
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        tot = 0;
        pos.clear();
        cand.clear();
        dfs(root);
        vector<TreeNode *> ret;
        for(auto &it: cand)
            if(it.size() == 2)
                ret.push_back(it.back());
        return ret;
    }
};
