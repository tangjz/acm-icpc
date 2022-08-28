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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int n = 0, m = 0;
        for(ListNode *ptr = headA; ptr != nullptr; ptr = ptr -> next, ++n);
        for(ListNode *ptr = headB; ptr != nullptr; ptr = ptr -> next, ++m);
        for( ; n > m; headA = headA -> next, --n);
        for( ; n < m; headB = headB -> next, --m);
        while(headA != headB) {
            headA = headA -> next;
            headB = headB -> next;
        }
        return headA;
    }
};
