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
    ListNode* mergeNodes(ListNode* head) {
        if(head == nullptr)
            return nullptr;
        if(head -> next == nullptr)
            return nullptr;
        int sum = 0;
        for(head = head -> next; head != nullptr && head -> val; sum += head -> val, head = head -> next);
        return new ListNode(sum, mergeNodes(head));
    }
};
