/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    void dfs(TreeNode *rt, vector<ListNode *> &ret, int dep) {
        if(rt == nullptr)
            return;
        if(dep == ret.size())
            ret.push_back(nullptr);
        ListNode *head = new ListNode(rt -> val);
        head -> next = ret[dep];
        ret[dep] = head;
        dfs(rt -> right, ret, dep + 1);
        dfs(rt -> left, ret, dep + 1);
    }
public:
    vector<ListNode*> listOfDepth(TreeNode* tree) {
        vector<ListNode *> ret;
        dfs(tree, ret, 0);
        return ret;
    }
};
