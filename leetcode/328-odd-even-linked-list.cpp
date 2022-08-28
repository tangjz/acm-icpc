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
    ListNode* oddEvenList(ListNode* head) {
        bool pos = 0;
        ListNode *new_head[2] = {}, *new_tail[2] = {};
        for(ListNode *ptr = head, *nxt; ptr != NULL; ptr = nxt, pos = !pos) {
            nxt = ptr -> next;
            ptr -> next = nxt != NULL ? nxt -> next : NULL;
            if(new_head[pos] == NULL)
                new_head[pos] = ptr;
            new_tail[pos] = ptr;
        }
        if(new_head[1] != NULL)
            new_tail[0] -> next = new_head[1];
        return new_head[0];
    }
};
