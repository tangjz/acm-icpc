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
    TreeNode* createBinaryTree(vector<vector<int>>& descriptions) {
        unordered_map<int, int> deg;
        unordered_map<int, TreeNode *> info;
        auto getNode = [&](int val) {
            auto it = info.find(val);
            if(it == info.end())
                return info[val] = new TreeNode(val);
            return it -> second;
        };
        for(auto &it: descriptions) {
            TreeNode *rt = getNode(it[0]), *tr = getNode(it[1]);
            ++deg[it[1]];
            (it[2] ? rt -> left : rt -> right) = tr;
        }
        for(auto &it: info)
            if(!deg.count(it.first))
                return it.second;
        return nullptr;
    }
};
