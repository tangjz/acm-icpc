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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        vector<ListNode*> seq;
        for(ListNode* ptr = head; ptr != nullptr; ptr = ptr -> next) {
            seq.push_back(ptr);
        }
        int n = seq.size();
        for(int i = 1, j = 0; j < n; j += i++) {
            int k = min(j + i, n);
            int len = k - j;
            if(len & 1)
                continue;
            reverse(seq.begin() + j, seq.begin() + k);
        }
        seq.push_back(nullptr);
        for(int i = 0; i < n; ++i)
            seq[i] -> next = seq[i + 1];
        return seq.front();
    }
};
