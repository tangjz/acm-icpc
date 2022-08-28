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
    typedef ListNode *Link;
    Link mergeList(Link lft, Link rht) {
        Link head = NULL, tail = NULL;
        while(lft != NULL || rht != NULL) {
            Link &cur = rht == NULL || (lft != NULL && (lft -> val) < (rht -> val)) ? lft : rht;
            if(head == NULL) {
                head = cur;
            } else {
                tail -> next = cur;
            }
            tail = cur;
            cur = cur -> next;
        }
        return head;
    }
public:
    ListNode* sortList(ListNode* head) {
        for(int step = 1; ; step <<= 1) {
            ListNode *lft = head, *rht, *tail = NULL, *tmp, *nxt;
            bool upd = 0;
            while(lft != NULL) {
                rht = lft;
                for(int i = 0; i < step && rht != NULL; ++i) {
                    tmp = rht;
                    rht = rht -> next;
                }
                if(rht == NULL) {
                    nxt = NULL;
                    tmp = lft;
                } else {
                    tmp -> next = NULL;
                    nxt = rht;
                    for(int i = 0; i < step && nxt != NULL; ++i) {
                        tmp = nxt;
                        nxt = nxt -> next;
                    }
                    tmp -> next = NULL;
                    tmp = mergeList(lft, rht);
                    upd = 1;
                }
                if(tail == NULL) {
                    head = tail = tmp;
                } else {
                    tail -> next = tmp;
                }
                while((tail -> next) != NULL)
                    tail = tail -> next;
                lft = nxt;
            }
            if(!upd)
                break;
        }
        return head;
    }
};
