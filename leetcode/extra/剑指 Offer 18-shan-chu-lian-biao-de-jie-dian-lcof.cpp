/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteNode(ListNode* head, int val) {
        if(head == nullptr)
            return head;
        if(head -> val == val)
            return head -> next;
        head -> next = deleteNode(head -> next, val);
        return head;
    }
};
