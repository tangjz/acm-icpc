class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [&](auto const &it, auto const &jt) {
            return it[1] < jt[1];
        });
        int ans = 1, las = points.front()[1];
        for(auto &it: points) {
            if(it[0] <= las)
                continue;
            ++ans;
            las = it[1];
        }
        return ans;
    }
};
