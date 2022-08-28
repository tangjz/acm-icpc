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
    pair<ListNode *, bool> calc(ListNode *ptr) {
        if(ptr -> next == nullptr) {
            ++(ptr -> val);
        } else {
            pair<ListNode*, bool> ret = calc(ptr -> next);
            ptr -> next = ret.first;
            ptr -> val += ret.second;
        }
        bool carry = ptr -> val >= 10;
        if(carry)
            ptr -> val -= 10;
        return {ptr, carry};
    }
public:
    ListNode* plusOne(ListNode* head) {
        pair<ListNode *, bool> ret = calc(head);
        return ret.second ? new ListNode(1, ret.first) : ret.first;
    }
};
