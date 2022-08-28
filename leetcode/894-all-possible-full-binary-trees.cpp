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
    vector<TreeNode*> allPossibleFBT(int n) {
        if(!(n & 1))
            return {};
        static map<int, vector<TreeNode *> > Hash;
        if(Hash.empty())
            Hash[1] = {new TreeNode(0)};
        auto it = Hash.find(n);
        if(it == Hash.end()) {
            vector<TreeNode *> vec;
            for(int i = 1; i + 1 < n; ++i)
                for(TreeNode *lft: allPossibleFBT(i))
                    for(TreeNode *rht: allPossibleFBT(n - 1 - i))
                        vec.push_back(new TreeNode(0, lft, rht));
            it = Hash.insert({n, vec}).first;
        }
        return it -> second;
    }
};
