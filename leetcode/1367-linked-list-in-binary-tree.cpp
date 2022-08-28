/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    bool isSubPath(ListNode* head, TreeNode* root, bool first = 1) {
        if(root == NULL || head == NULL)
            return head == NULL;
        if(first) {
            if(isSubPath(head, root -> left, 1) || isSubPath(head, root -> right, 1))
                return 1;
        }
        if(head -> val != root -> val)
            return 0;
        return isSubPath(head -> next, root -> left, 0) || isSubPath(head -> next, root -> right, 0);
    }
};
