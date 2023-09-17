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
    vector<ListNode*> splitCircularLinkedList(ListNode* list) {
        int sz = 1;
        ListNode *p, *q;
        for(p = list; p -> next != list; p = p -> next, ++sz);
        q = list;
        for(int i = 2; i < sz; i += 2)
            q = q -> next;
        p -> next = q -> next;
        q -> next = list;
        return {list, p -> next};
    }
};
