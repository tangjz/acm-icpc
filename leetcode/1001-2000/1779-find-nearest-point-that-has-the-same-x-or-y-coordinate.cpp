class Solution {
public:
    int nearestValidPoint(int x, int y, vector<vector<int>>& points) {
        int best = INT_MAX, ans = -1, pos = 0;
        for(auto &it: points) {
            int u = it[0], v = it[1];
            if(u == x || v == y) {
                int cur = abs(u - x) + abs(v - y);
                if(best > cur) {
                    best = cur;
                    ans = pos;
                }
            }
            ++pos;
        }
        return ans;
    }
};
