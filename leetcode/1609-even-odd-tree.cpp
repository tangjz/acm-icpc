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
    bool isEvenOddTree(TreeNode* root) {
        int sgn = -1, odd = 1;
        vector<TreeNode *> f = {root};
        while(!f.empty()) {
            TreeNode *las = nullptr;
            vector<TreeNode *> g;
            for(TreeNode *cur: f) {
                for(TreeNode *nxt: {cur -> left, cur -> right})
                    if(nxt != nullptr)
                        g.push_back(nxt);
                if((cur -> val & 1) != odd)
                    return false;
                if(las != nullptr) {
                    int dif = las -> val - cur -> val;
                    if((dif > 0) - (dif < 0) != sgn)
                        return false;
                }
                las = cur;
            }
            sgn = -sgn;
            odd = !odd;
            f = move(g);
        }
        return true;
    }
};
