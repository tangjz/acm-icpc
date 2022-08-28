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
    ListNode *detectCycle(ListNode *head) {
        ListNode *p = head, *q = head;
        while(q != nullptr) {
            q = q -> next;
            if(q != nullptr)
                q = q -> next;
            p = p -> next;
            if(p == q)
                break;
        }
        if(q == nullptr)
            return nullptr;
        q = head;
        while(p != q) {
            p = p -> next;
            q = q -> next;
        }
        return p;
    }
};
