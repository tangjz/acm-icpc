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
    ListNode* removeNodes(ListNode* head) {
        if(head != nullptr) {
            head -> next = removeNodes(head -> next);
            if(head -> next != nullptr && head -> val < head -> next -> val)
                head = head -> next;
        }
        return head;
    }
};
