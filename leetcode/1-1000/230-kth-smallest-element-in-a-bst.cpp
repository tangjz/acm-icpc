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
    int kthSmallest(TreeNode* root, int k) {
        stack<pair<TreeNode *, int> > stk;
        stk.push(make_pair(root, 0));
        while(!stk.empty()) {
            TreeNode *cur, *nxt = NULL;
            int ctr;
            tie(cur, ctr) = stk.top();
            stk.pop();
            if(ctr == 0) {
                nxt = cur -> left;
            } else if(ctr == 1) {
                if(!(--k))
                    return cur -> val;
                nxt = cur -> right;
            }
            if((++ctr) < 2)
                stk.push(make_pair(cur, ctr));
            if(nxt != NULL)
                stk.push(make_pair(nxt, 0));
        }
        assert(0);
    }
};
