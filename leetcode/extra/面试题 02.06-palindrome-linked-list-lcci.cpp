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
    bool isPalindrome(ListNode* head) {
        if(head == nullptr)
            return 1;
        ListNode *u = head, *v = head, *w = nullptr;
        for( ; v -> next != nullptr && (v -> next) -> next != nullptr; u = u -> next, v = (v -> next) -> next);
        for(u = u -> next; u != nullptr; ) {
            v = u -> next;
            u -> next = w;
            w = u;
            u = v;
        }
        for(u = head; w != nullptr; u = u -> next, w = w -> next)
            if(u -> val != w -> val)
                return 0;
        return 1;
    }
};
