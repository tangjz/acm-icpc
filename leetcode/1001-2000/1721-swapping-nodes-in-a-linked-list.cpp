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
    ListNode* swapNodes(ListNode* head, int k) {
        vector<ListNode *> vec;
        for(ListNode *ptr = head; ptr; ptr = ptr -> next)
            vec.push_back(ptr);
        int sz = (int)vec.size();
        vec.push_back(nullptr);
        int u = k - 1, v = sz - k;
        if(u == v)
            return head;
        if(u > v)
            swap(u, v);
        swap(vec[u], vec[v]);
        for(int i = u - 1; i <= u; ++i)
            if(i >= 0)
                vec[i] -> next = vec[i + 1];
        for(int i = v - 1; i <= v; ++i)
            if(i >= 0)
                vec[i] -> next = vec[i + 1];
        return vec.front();
    }
};
