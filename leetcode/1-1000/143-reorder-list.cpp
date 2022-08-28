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
    void reorderList(ListNode* head) {
        if(head == nullptr)
            return;
        ListNode *p, *q, *r;
        for(p = q = head; q -> next != nullptr && (q -> next) -> next != nullptr; p = p -> next, q = (q -> next) -> next);
        ListNode *head2 = nullptr;
        for(q = p -> next; q != nullptr; ) {
            r = q -> next;
            q -> next = head2;
            head2 = q;
            q = r;
        }
        p -> next = NULL;
        for(p = head, q = head2; q != nullptr; ) {
            // assert(p);
            r = q -> next;
            q -> next = p -> next;
            p -> next = q;
            p = q -> next;
            q = r;
        }
    }
};
