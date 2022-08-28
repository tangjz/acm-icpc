class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0, x = points[0][0], y = points[0][1];
        for(auto &it : points) {
            ans += max(abs(it[0] - x), abs(it[1] - y));
            x = it[0];
            y = it[1];
        }
        return ans;
    }
};
