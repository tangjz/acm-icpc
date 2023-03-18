class Solution {
public:
    int countWays(vector<vector<int>>& ranges) {
        const int mod = (int)1e9 + 7;
        int n = ranges.size(), ans = 2;
        sort(ranges.begin(), ranges.end());
        for(int i = 0, las = ranges[0][1]; i + 1 < n; ++i) {
            las = max(las, ranges[i][1]);
            if(las < ranges[i + 1][0])
                (ans <<= 1) >= mod && (ans -= mod);
        }
        return ans;
    }
};
