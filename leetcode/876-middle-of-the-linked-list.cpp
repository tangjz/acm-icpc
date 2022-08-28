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
    ListNode* middleNode(ListNode* head) {
        ListNode *ptr;
        int ctr = 0;
        for(ptr = head; ptr != NULL; ptr = ptr -> next)
            ++ctr;
        ctr = ctr >> 1;
        for(ptr = head; ctr > 0; --ctr)
            ptr = ptr -> next;
        return ptr;
    }
};
