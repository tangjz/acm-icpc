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
    TreeNode* findNearestRightNode(TreeNode* root, TreeNode* u) {
        stack<pair<TreeNode *, int> > stk;
        for(int lev = 0; root != nullptr; root = root -> left, ++lev)
            stk.push({root, lev});
        auto ext = [&]() {
            pair<TreeNode *, int> cur = stk.top();
            stk.pop();
            for(cur.first = (cur.first) -> right, ++cur.second; cur.first != nullptr; cur.first = (cur.first) -> left, ++cur.second)
                stk.push(cur);
        };
        while(stk.top().first != u)
            ext();
        int lev = stk.top().second;
        ext();
        while(!stk.empty() && stk.top().second != lev)
            ext();
        return stk.empty() ? nullptr : stk.top().first;
    }
};
