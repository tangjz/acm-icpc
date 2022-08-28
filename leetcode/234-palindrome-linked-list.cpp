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
    bool isPalindrome(ListNode* head) {
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
