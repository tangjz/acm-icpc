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
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> vals, pR;
        for( ; head != nullptr; head = head -> next)
            vals.push_back(head -> val);
        int n = vals.size();
        pR.resize(n);
        for(int i = n - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < n && vals[i] >= vals[pR[i]]; pR[i] = pR[pR[i]]);
        for(int &x: pR)
            x = x < n ? vals[x] : 0;
        return pR;
    }
};
