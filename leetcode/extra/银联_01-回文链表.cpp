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
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        for( ; head != nullptr; head = head -> next)
            vals.push_back(head -> val);
        int L = 0, R = vals.size() - 1;
        for( ; L < R && vals[L] == vals[R]; ++L, --R);
        if(L >= R)
            return 1;
        auto check = [&](int L, int R) -> bool {
            for( ; L < R && vals[L] == vals[R]; ++L, --R);
            return L >= R;
        };
        return check(L + 1, R) || check(L, R - 1);
    }
};
