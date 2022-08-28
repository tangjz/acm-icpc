class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
        if(intervals.empty())
            return 1;
        sort(intervals.begin(), intervals.end());
        int las = intervals.front()[0];
        for(auto &it: intervals) {
            if(it[0] < las)
                return 0;
            las = it[1];
        }
        return 1;
    }
};
