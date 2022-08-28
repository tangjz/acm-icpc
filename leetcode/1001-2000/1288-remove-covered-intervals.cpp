class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& seg) {
        for(auto &it : seg)
            it[1] = -it[1];
        sort(seg.begin(), seg.end());
        for(auto &it : seg)
            it[1] = -it[1];
        int cnt = 0, las = seg[0][0] - 1;
        for(auto &it : seg) {
            cnt += las < it[1];
            las = max(las, it[1]);
        }
        return cnt;
    }
};
