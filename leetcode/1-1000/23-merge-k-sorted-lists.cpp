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
                head = tail = cur;
                cur = cur -> next;
            } else {
                tail -> next = cur;
                tail = cur;
                cur = cur -> next;
            }
        }
        return head;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n = (int)lists.size();
        vector<ListNode *> vec(lists.begin(), lists.end());
        for(int i = 1; i < n; i <<= 1)
            for(int j = 0; j + i < n; j += i + i)
                vec[j] = mergeList(vec[j], vec[j + i]);
        return n ? vec[0] : NULL;
    }
};
