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
        if(head == nullptr)
            return nullptr;
        ListNode *nxt = head -> next;
        while(nxt != nullptr && nxt -> val == head -> val)
            nxt = nxt -> next;
        head -> next = deleteDuplicates(nxt);
        return head;
    }
};
