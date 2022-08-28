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
class Solution {
public:
    ListNode* deleteMiddle(ListNode* head) {
        int n = 0;
        for(ListNode *ptr = head; ptr != nullptr; ptr = ptr -> next, ++n);
        if(n == 1)
            return nullptr;
        ListNode *p = head, *q = p -> next;
        for(int i = 1; i < n / 2; ++i, p = q, q = p -> next);
        p -> next = q -> next;
        return head;
    }
};
