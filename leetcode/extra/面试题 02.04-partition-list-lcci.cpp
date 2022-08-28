/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        typedef pair<ListNode *, ListNode *> Info;
        Info low = {}, upp = {};
        for(ListNode *nxt; head != nullptr; head = nxt) {
            nxt = head -> next;
            head -> next = nullptr;
            Info &cur = head -> val < x ? low : upp;
            if(cur.first == nullptr) {
                cur = {head, head};
            } else {
                cur.second -> next = head;
                cur.second = head;
            }
        }
        if(low.first == nullptr)
            return upp.first;
        low.second -> next = upp.first;
        return low.first;
    }
};
