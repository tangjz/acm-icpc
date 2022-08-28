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
    ListNode* sortLinkedList(ListNode* head) {
        if(head != nullptr) {
            ListNode *tail = head, *ptr = tail -> next;
            for( ; ptr != nullptr; ptr = tail -> next)
                if(ptr -> val < 0) {
                    tail -> next = ptr -> next;
                    ptr -> next = head;
                    head = ptr;
                } else {
                    tail = ptr;
                }
        }
        return head;
    }
};
