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
    mt19937 rnd;
    ListNode *head;
public:
    /** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
    Solution(ListNode* head) {
        rnd.seed(19260817);
        this -> head = head;
    }
    
    /** Returns a random node's value. */
    int getRandom() {
        int val = 0, ctr = 0;
        for(ListNode *ptr = head; ptr != NULL; ptr = ptr -> next)
            if(rnd() % (++ctr) == 0)
                val = ptr -> val;
        return val;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */
