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
    ListNode* swapPairs(ListNode* head) {
        ListNode *pre = NULL, *cur = head, *nxt, *tmp;
        while(cur != NULL && (nxt = cur -> next) != NULL) {
            tmp = nxt -> next;
            nxt -> next = cur;
            cur -> next = tmp;
            if(pre == NULL) {
                head = nxt;
            } else {
                pre -> next = nxt;
            }
            pre = cur;
            cur = tmp;
        }
        return head;
    }
};
