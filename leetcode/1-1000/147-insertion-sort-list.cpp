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
    ListNode* insertionSortList(ListNode* head) {
        ListNode *ret = new ListNode(INT_MIN), *ptr, *tmp;
        while(head != nullptr) {
            for(ptr = ret; ptr -> next != nullptr && (ptr -> next) -> val < head -> val; ptr = ptr -> next);
            tmp = ptr -> next;
            ptr -> next = head;
            head = head -> next;
            (ptr -> next) -> next = tmp;
        }
        return ret -> next;
    }
};
