/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        typedef pair<TreeNode *, int> State;
        bool vis = 0;
        TreeNode *com = NULL;
        stack<State> stk;
        stk.push(make_pair(root, 0));
        while(!stk.empty()) {
            State cur = stk.top();
            stk.pop();
            if(cur.second < 2) {
                TreeNode *nxt = NULL;
                if(!cur.second) { // first visiting
                    if(cur.first == p || cur.first == q) {
                        if(!vis) {
                            vis = 1;
                            com = cur.first;
                        } else {
                            break;
                        }
                    }
                    nxt = cur.first -> left;
                } else {
                    nxt = cur.first -> right;
                }
                ++cur.second;
                stk.push(cur);
                if(nxt != NULL)
                    stk.push(make_pair(nxt, 0));
            } else if(com == cur.first) {
                com = stk.top().first;
            }
        }
        return com;
    }
};
