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
    TreeNode* getTargetCopy(TreeNode* original, TreeNode* cloned, TreeNode* target) {
        typedef pair<TreeNode *, TreeNode *> Info;
        stack<Info> stk;
        auto extend = [&](Info rt) {
            for( ; rt.first != nullptr; rt = {rt.first -> left, rt.second -> left}) {
                stk.push(rt);
                if(rt.first == target)
                    break;
            }
        };
        extend({original, cloned});
        while(!stk.empty() && stk.top().first != target) {
            Info cur = stk.top();
            stk.pop();
            extend({cur.first -> right, cur.second -> right});
        }
        return stk.top().second;
    }
};
