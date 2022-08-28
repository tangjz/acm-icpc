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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *pre = nullptr, *cur = head, *nxt = nullptr;
        for(int i = 1; i < left; ++i) {
            pre = cur;
            cur = cur -> next;
        }
        ListNode *mid = nullptr;
        for(int i = left; i <= right; ++i) {
            nxt = cur -> next;
            cur -> next = mid;
            mid = cur;
            cur = nxt;
        }
        nxt = cur;
        if(pre == nullptr) {
            cur = head;
            head = mid;
        } else {
            cur = pre -> next;
            pre -> next = mid;
        }
        cur -> next = nxt;
        return head;
    }
};
