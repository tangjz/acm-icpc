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
    ListNode* reContruct(ListNode* head) {
        if(head != nullptr) {
            head -> next = reContruct(head -> next);
            if(!(head -> val & 1))
                head = head -> next;
        }
        return head;
    }
};
