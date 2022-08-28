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
    pair<int, int> dfs(TreeNode *rt, unordered_map<int, int> &pos, bool &valid, vector<int> &ops) {
        pair<int, int> mid = {-1, -1};
        if(rt == nullptr || !valid)
            return mid;
        auto it = pos.find(rt -> val);
        if(it == pos.end()) {
            valid = 0;
            return mid;
        }
        mid.first = mid.second = it -> second;
        pair<int, int> lft = dfs(rt -> left, pos, valid, ops);
        if(!valid)
            return mid;
        pair<int, int> rht = dfs(rt -> right, pos, valid, ops);
        if(!valid)
            return mid;
        if(lft.second != -1 && rht.first != -1 && lft.second > rht.first) {
            swap(lft, rht);
            ops.push_back(rt -> val);
        }
        if(lft.first != -1) {
            if(lft.first != mid.second + 1) {
                valid = 0;
                return mid;
            }
            mid.second = lft.second;
        }
        if(rht.first != -1) {
            if(rht.first != mid.second + 1) {
                valid = 0;
                return mid;
            }
            mid.second = rht.second;
        }
        // printf("dfs %d: %d %d\n", rt -> val, mid.first, mid.second);
        return mid;
    }
public:
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        unordered_map<int, int> pos;
        for(int i = 0; i < voyage.size(); ++i)
            pos[voyage[i]] = i;

        bool valid = 1;
        vector<int> ops;
        dfs(root, pos, valid, ops);
        if(!valid)
            return {-1};
        return ops;
    }
};
