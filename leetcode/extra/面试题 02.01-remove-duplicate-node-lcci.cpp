/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    ListNode *dfs(ListNode* head, unordered_set<int> &sp) {
        if(head == nullptr)
            return nullptr;
        ListNode* &ptr = (sp.insert(head -> val).second ? head -> next : head);
        ptr = dfs(head -> next, sp);
        return head;
    }
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        unordered_set<int> sp;
        return dfs(head, sp);
    }
};
