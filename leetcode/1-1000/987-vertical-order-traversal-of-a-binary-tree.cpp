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
    void dfs(TreeNode *rt, int r, int c, map<int, map<int, vector<int> > > &hs) {
        if(rt == nullptr)
            return;
        hs[c][r].push_back(rt -> val);
        dfs(rt -> left, r + 1, c - 1, hs);
        dfs(rt -> right, r + 1, c + 1, hs);
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        map<int, map<int, vector<int> > > hs;
        dfs(root, 0, 0, hs);
        vector<vector<int> > ret;
        for(auto &it: hs) {
            int i = it.first;
            vector<int> tmp;
            for(auto &jt: it.second) {
                int j = jt.first;
                auto &vec = jt.second;
                sort(vec.begin(), vec.end());
                tmp.insert(tmp.end(), vec.begin(), vec.end());
            }
            ret.push_back(move(tmp));
        }
        return ret;
    }
};
