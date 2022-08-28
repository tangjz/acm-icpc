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
public:
    TreeNode* canMerge(vector<TreeNode*>& trees) {
        unordered_map<int, TreeNode*> Hash;
        unordered_map<int, int> deg;
        for(TreeNode *rt: trees) {
            Hash[rt -> val] = rt;
            for(TreeNode *ch: {rt -> left, rt -> right})
                if(ch != nullptr)
                    ++deg[ch -> val];
        }
        vector<pair<TreeNode *, pair<int, int> > > que;
        for(TreeNode *rt: trees) {
            int id = rt -> val;
            if(!deg.count(id))
                que.push_back({rt, {0, INT_MAX}});
            if(deg[id] > 1)
                return nullptr;
        }
        if(que.size() > 1)
            return nullptr;
        for(int i = 0; i < (int)que.size(); ++i) {
            TreeNode *rt = que[i].first;
            int vL = que[i].second.first, vR = que[i].second.second;
            int mid = rt -> val;
            if(mid <= vL || mid >= vR)
                return nullptr;
            if(rt -> left != nullptr) {
                int lft = rt -> left -> val;
                if(lft <= vL || lft >= mid)
                    return nullptr;
                if(Hash.count(lft)) {
                    rt -> left = Hash[lft];
                    que.push_back({rt -> left, {vL, mid}});
                }
            }
            if(rt -> right != nullptr) {
                int rht = rt -> right -> val;
                if(rht <= mid || rht >= vR)
                    return nullptr;
                if(Hash.count(rht)) {
                    rt -> right = Hash[rht];
                    que.push_back({rt -> right, {mid, vR}});
                }
            }
            if(que.size() > trees.size())
                return nullptr;
        }
        if(que.size() != trees.size())
            return nullptr;
        return que.front().first;
    }
};
