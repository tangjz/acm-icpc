/**
 * // This is Sea's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Sea {
 *   public:
 *     bool hasShips(vector<int> topRight, vector<int> bottomLeft);
 * };
 */

class Solution {
public:
    int countShips(Sea sea, vector<int> topRight, vector<int> bottomLeft) {
        int ans = 0;
        int xL = bottomLeft[0], yL = bottomLeft[1];
        int xR = topRight[0], yR = topRight[1];
        while(xL <= xR && yL <= yR && sea.hasShips({xR, yR}, {xL, yL})) {
            int L = xL, R = xR;
            while(L < R) {
                int M = (L + R) >> 1;
                if(sea.hasShips({M, yR}, {xL, yL})) {
                    R = M;
                } else {
                    L = M + 1;
                }
            }
            xL = L;
            L = yL;
            do {
                R = yR;
                while(L < R) {
                    int M = (L + R) >> 1;
                    if(sea.hasShips({xL, M}, {xL, L})) {
                        R = M;
                    } else {
                        L = M + 1;
                    }
                }
                ++ans;
                ++L;
            } while(L <= yR && sea.hasShips({xL, yR}, {xL, L}));
            ++xL;
        }
        return ans;
    }
};
