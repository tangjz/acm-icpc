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
    typedef pair<ListNode *, ListNode *> List;
    void addHead(List &cur, ListNode *adt) {
        if(cur.first == NULL) {
            cur.first = cur.second = adt;
            adt -> next = NULL;
        } else {
            adt -> next = cur.first;
            cur.first = adt;
        }
    }
    void merge(List &cur, List &nxt) {
        if(cur.first == NULL) {
            cur = nxt;
        } else if(nxt.first != NULL) {
            cur.second -> next = nxt.first;
            cur.second = nxt.second;
        }
        nxt = {NULL, NULL};
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        List cur = {NULL, NULL}, nxt = {NULL, NULL};
        for(ListNode *it = head, *jt; it != NULL; ) {
            int ctr = 0;
            for(jt = it; jt != NULL && ctr < k; jt = jt -> next, ++ctr);
            if(ctr < k) {
                nxt = {it, NULL};
                merge(cur, nxt);
                break;
            }
            for(ctr = 0; ctr < k; it = jt, ++ctr) {
                jt = it -> next;
                addHead(nxt, it);
            }
            merge(cur, nxt);
        }
        return cur.first;
    }
};
