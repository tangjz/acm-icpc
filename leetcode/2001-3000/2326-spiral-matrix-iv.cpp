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
    vector<vector<int>> spiralMatrix(int r, int c, ListNode* head) {
        vector<vector<int> > ret(r, vector<int>(c, -1));
        for(int xL = 0, xR = r - 1, yL = 0, yR = c - 1; head != nullptr; ++xL, --xR, ++yL, --yR) {
            if(xL == xR) {
                for(int y = yL; y <= yR && head != nullptr; ++y, head = head -> next)
                    ret[xL][y] = head -> val;
                continue;
            }
            if(yL == yR) {
                for(int x = xL; x <= xR && head != nullptr; ++x, head = head -> next)
                    ret[x][yR] = head -> val;
                continue;
            }
            for(int y = yL; y < yR && head != nullptr; ++y, head = head -> next)
                ret[xL][y] = head -> val;
            for(int x = xL; x < xR && head != nullptr; ++x, head = head -> next)
                ret[x][yR] = head -> val;
            for(int y = yR; y > yL && head != nullptr; --y, head = head -> next)
                ret[xR][y] = head -> val;
            for(int x = xR; x > xL && head != nullptr; --x, head = head -> next)
                ret[x][yL] = head -> val;
        }
        return ret;
    }
};
