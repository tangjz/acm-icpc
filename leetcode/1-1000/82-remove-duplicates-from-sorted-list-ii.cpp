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
    ListNode* deleteDuplicates(ListNode* head) {
        if(head != nullptr) {
            ListNode *ptr = head;
            while(ptr -> next != nullptr && ptr -> next -> val == ptr -> val) {
                ptr = ptr -> next;
            }
            if(head == ptr) {
                head -> next = deleteDuplicates(ptr -> next);
            } else {
                head = deleteDuplicates(ptr -> next);
            }
        }
        return head;
    }
};
