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
    int calc(ListNode *head) {
        if(head == nullptr)
            return 0;
        int adt = calc(head -> next) + head -> val * 2;
        head -> val = adt % 10;
        return adt / 10;
    }
public:
    ListNode* doubleIt(ListNode* head) {
        int res = calc(head);
        if(res)
            head = new ListNode(res, head);
        return head;
    }
};
