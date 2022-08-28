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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        TreeNode *pre, *cur, *nxt;
        stack<TreeNode *> stk;
        for(int x: nums) {
            pre = nullptr;
            nxt = new TreeNode(x);
            while(!stk.empty() && (cur = stk.top()) -> val < nxt -> val) {
                if(pre != nullptr)
                    cur -> right = pre;
                stk.pop();
                pre = cur;
            }
            if(pre != nullptr)
                nxt -> left = pre;
            stk.push(nxt);
        }
        pre = nullptr;
        while(!stk.empty()) {
            cur = stk.top();
            if(pre != nullptr)
                cur -> right = pre;
            stk.pop();
            pre = cur;
        }
        return pre;
    }
};
