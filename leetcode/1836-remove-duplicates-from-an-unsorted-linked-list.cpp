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
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        unordered_map<int, int> ctr;
        for(ListNode *ptr = head; ptr != nullptr; ptr = ptr -> next)
            ++ctr[ptr -> val];
        ListNode *ret = nullptr, *tail = nullptr;
        for(ListNode *ptr = head; ptr != nullptr; ptr = ptr -> next) {
            if(ctr[ptr -> val] != 1)
                continue;
            if(ret == nullptr) {
                ret = tail = ptr;
            } else {
                tail -> next = ptr;
                tail = ptr;
            }
        }
        if(tail != nullptr)
            tail -> next = nullptr;
        return ret;
    }
};
