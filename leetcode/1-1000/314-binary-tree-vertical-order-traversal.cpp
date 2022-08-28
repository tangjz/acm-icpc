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
    void dfs(TreeNode *rt, int x, int y, int &low, deque<vector<vector<int> > > &vals) {
        if(rt == nullptr)
            return;
        for( ; y < low; vals.push_front({}), --low);
        for(int upp = low + vals.size(); y >= upp; vals.push_back({}), ++upp);
        for(int sz = vals[y - low].size(); x >= sz; vals[y - low].push_back({}), ++sz);
        vals[y - low][x].push_back(rt -> val);
        dfs(rt -> left, x + 1, y - 1, low, vals);
        dfs(rt -> right, x + 1, y + 1, low, vals);
    }
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        int low = 0;
        deque<vector<vector<int> > > vals;
        dfs(root, 0, 0, low, vals);
        vector<vector<int> > ret;
        ret.reserve(vals.size());
        while(!vals.empty()) {
            auto &it = vals.front();
            vector<int> adt;
            for(auto &jt: it)
                adt.insert(adt.end(), jt.begin(), jt.end());
            vals.pop_front();
            if(!adt.empty())
                ret.push_back(move(adt));
        }
        return ret;
    }
};
