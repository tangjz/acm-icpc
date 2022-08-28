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
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr)
            return nullptr;
        int m = 0;
        ListNode *ptr = head;
        for(m = 0; m < k && ptr != nullptr; ++m, ptr = ptr -> next);
        if(ptr == nullptr) {
            k %= m;
            for(m = 0, ptr = head; m < k; ++m, ptr = ptr -> next);
        }
        ListNode *tail = head;
        for( ; ptr -> next != nullptr; ptr = ptr -> next, tail = tail -> next);
        ptr -> next = head;
        head = tail -> next;
        tail -> next = nullptr;
        return head;
    }
};
