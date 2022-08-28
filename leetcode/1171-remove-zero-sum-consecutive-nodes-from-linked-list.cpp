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
    ListNode* removeZeroSumSublists(ListNode* head) {
        if(head != nullptr) {
            head -> next = removeZeroSumSublists(head -> next);
            int s = 0;
            for(ListNode *ptr = head; ptr != nullptr; ptr = ptr -> next) {
                s += ptr -> val;
                if(!s) {
                    head = ptr -> next;
                    break;
                }
            }
        }
        return head;
    }
};
