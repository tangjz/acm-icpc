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
    vector<ListNode*> splitListToParts(ListNode* head, int k) {
        int n = 0;
        ListNode *ptr;
        for(ptr = head; ptr != nullptr; ptr = ptr -> next, ++n);
        vector<ListNode *> ret(k);
        for(int i = 0; i < k; ++i) {
            int step = n / k + (i < n % k);
            ret[i] = head;
            for( ; step--; ptr = head, head = ptr -> next);
            if(ptr != nullptr)
                ptr -> next = nullptr;
        }
        return ret;
    }
};
