class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(), [](auto const &it, auto const &jt) {
            return it.back() < jt.back();
        });
        int ret = 0, las = intervals.front().front();
        for(auto const &it : intervals) {
            if(it.front() < las) {
                ++ret;
            } else {
                las = it.back();
            }
        }
        return ret;
    }
};
