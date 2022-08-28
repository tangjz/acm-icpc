class Solution {
public:
    vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
        vector<vector<int> > ret;
        for(auto &it: intervals) {
            int low = max(it[0], toBeRemoved[0]);
            int upp = min(it[1], toBeRemoved[1]);
            if(low <= it[0] && it[1] <= upp)
                continue;
            if(low <= upp) {
                if(low == it[0]) {
                    it[0] = upp;
                } else if(upp == it[1]) {
                    it[1] = low;
                } else {
                    ret.push_back({it[0], low});
                    it[0] = upp;
                }
            }
            ret.push_back(it);
        }
        return ret;
    }
};
