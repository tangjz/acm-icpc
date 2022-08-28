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
    int sgn(int x) {
        return (x > 0) - (x < 0);
    }
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        ListNode *prev = nullptr;
        int firPos = -1, curPos = 0, lasPos = -1;
        int minDis = INT_MAX;
        for(ListNode *p = head; p != nullptr; prev = p, p = p -> next, ++curPos) {
            int sgn1 = prev == nullptr ? 0 : sgn(p -> val - prev -> val);
            int sgn2 = p -> next == nullptr ? 0 : sgn(p -> val - p -> next -> val);
            if(sgn1 * sgn2 <= 0)
                continue;
            if(firPos == -1) {
                firPos = curPos;
            }
            if(lasPos != -1) {
                minDis = min(minDis, curPos - lasPos);
            }
            lasPos = curPos;
        }
        if(minDis == INT_MAX)
            return {-1, -1};
        return {minDis, lasPos - firPos};
    }
};
