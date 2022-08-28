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
    ListNode* deleteNodes(ListNode* head, int m, int n) {
        ListNode *ptr = head, *nxt;
        while(1) {
            for(int i = 1; i < m && ptr != nullptr; ++i)
                ptr = ptr -> next;
            if(ptr == nullptr)
                break;
            nxt = ptr -> next;
            for(int i = 0; i < n && nxt != nullptr; ++i)
                nxt = nxt -> next;
            ptr -> next = nxt;
            ptr = nxt;
        }
        return head;
    }
};
