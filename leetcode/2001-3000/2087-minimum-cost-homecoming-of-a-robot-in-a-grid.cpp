class Solution {
public:
    int minCost(vector<int>& startPos, vector<int>& homePos, vector<int>& rowCosts, vector<int>& colCosts) {
        int x1 = startPos[0], y1 = startPos[1];
        int x2 = homePos[0], y2 = homePos[1];
        int ans = 0;
        if(x1 > x2) {
            for(int i = x2; i < x1; ++i)
                ans += rowCosts[i];
        } else {
            for(int i = x1 + 1; i <= x2; ++i)
                ans += rowCosts[i];
        }
        if(y1 > y2) {
            for(int i = y2; i < y1; ++i)
                ans += colCosts[i];
        } else {
            for(int i = y1 + 1; i <= y2; ++i)
                ans += colCosts[i];
        }
        return ans;
    }
};
