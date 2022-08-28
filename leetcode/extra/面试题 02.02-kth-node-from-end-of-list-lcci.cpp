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
    int kthToLast(ListNode* head, int k) {
        ListNode *ptr = head;
        while(k--)
            ptr != nullptr && (ptr = ptr -> next);
        for( ; ptr != nullptr; ptr = ptr -> next, head = head -> next);
        return head -> val;
    }
};
