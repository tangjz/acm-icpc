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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = NULL, *tail = NULL;
        auto append = [&](int val) -> void {
            ListNode *ptr = new ListNode(val);
            if(head == NULL) {
                head = tail = ptr;
            } else {
                tail -> next = ptr;
                tail = ptr;
            }
        };
        int adt = 0;
        for(ListNode *it = l1, *jt = l2; it != NULL || jt != NULL; ) {
            int sum = adt;
            if(it != NULL) {
                sum += it -> val;
                it = it -> next;
            }
            if(jt != NULL) {
                sum += jt -> val;
                jt = jt -> next;
            }
            if(sum >= 10) {
                adt = 1;
                sum -= 10;
            } else {
                adt = 0;
            }
            append(sum);
        }
        if(adt == 1) {
            append(adt);
        }
        return head;
    }
};
