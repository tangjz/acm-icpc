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
    bool hasCycle(ListNode *head) {
        if(head == nullptr)
            return false;
        for(ListNode *p = head -> next, *q = p != nullptr ? p -> next : nullptr; p != nullptr && q != nullptr; p = p -> next, q = q -> next != nullptr ? (q -> next) -> next : nullptr)
            if(p == q)
                return true;
        return false;
    }
};
