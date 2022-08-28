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
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> Hash;
        for(int x: nums)
            Hash.insert(x);
        int ans = 0;
        while(head != nullptr) {
            if(!Hash.count(head -> val)) {
                head = head -> next;
                continue;
            }
            for(++ans, head = head -> next; head != nullptr && Hash.count(head -> val); head = head -> next);
        }
        return ans;
    }
};
