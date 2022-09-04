class Solution {
public:
    vector<int> explorationSupply(vector<int>& station, vector<int>& pos) {
        const int INF = 0x3f3f3f3f;
        vector<int> ans;
        for(int x: pos) {
            pair<int, int> ret = {INF, -1};
            auto it = lower_bound(station.begin(), station.end(), x);
            if(it != station.end() && abs(ret.first - x) >= abs(*it - x)) {
                ret = {*it, it - station.begin()};
            }
            if(it != station.begin() && abs(ret.first - x) >= abs(*(--it) - x)) {
                ret = {*it, it - station.begin()};
            }
            ans.push_back(ret.second);
        }
        return ans;
    }
};
