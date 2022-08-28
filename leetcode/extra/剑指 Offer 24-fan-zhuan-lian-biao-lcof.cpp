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
    ListNode* reverseList(ListNode* head) {
        ListNode *ret = nullptr, *p;
        while(head != nullptr) {
            p = head;
            head = head -> next;
            p -> next = ret;
            ret = p;
        }
        return ret;
    }
};
