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
    ListNode* deleteListNode(ListNode* head) {
        if(head != nullptr && head -> next != nullptr)
            head -> next = deleteListNode(head -> next -> next);
        return head;
    }
};
