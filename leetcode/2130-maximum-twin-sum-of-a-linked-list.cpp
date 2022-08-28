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
    int pairSum(ListNode* head) {
        vector<int> vals;
        for( ; head != nullptr; head = head -> next)
            vals.push_back(head -> val);
        int n = vals.size();
        int ans = vals.front() + vals.back();
        for(int i = 1, j = n - 2; i < j; ++i, --j)
            ans = max(ans, vals[i] + vals[j]);
        return ans;
    }
};
