/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    void dfs(ListNode *head, vector<int> &ret) {
        if(head == nullptr)
            return;
        dfs(head -> next, ret);
        ret.push_back(head -> val);
    }
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> ret;
        dfs(head, ret);
        return ret;
    }
};
