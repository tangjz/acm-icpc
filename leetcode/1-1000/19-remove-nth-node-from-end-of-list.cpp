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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *pL = head, *pR = pL;
        while(n--) {
            pR = pR -> next;
        }
        ListNode *pre = NULL;
        while(pR != NULL) {
            pre = pL;
            pL = pL -> next;
            pR = pR -> next;
        }
        if(pre == NULL)
            return head -> next;
        pre -> next = pL -> next;
        return head;
    }
};
