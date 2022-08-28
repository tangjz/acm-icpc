class Solution {
    bool update(vector<int> const &lft, vector<int> &rht) {
        if(max(lft[0], rht[0]) <= min(lft[1], rht[1])) {
            rht[0] = min(rht[0], lft[0]);
            rht[1] = max(rht[1], lft[1]);
            return 1;
        }
        return 0;
    }
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = (int)intervals.size();
        for(int i = 0; i < n; ++i)
            if(update(intervals[i], newInterval))
                intervals[i][0] = INT_MAX;
        intervals.push_back(newInterval);
        sort(intervals.begin(), intervals.end());
        while(intervals.back()[0] == INT_MAX)
            intervals.pop_back();
        return intervals;
    }
};
