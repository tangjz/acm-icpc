class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        if(timePoints.size() >= 1440)
            return 0;
        vector<int> vals;
        for(auto &it: timePoints)
            vals.push_back(stoi(it.substr(0, 2)) * 60 + stoi(it.substr(3)));
        sort(vals.begin(), vals.end());
        if(unique(vals.begin(), vals.end()) != vals.end())
            return 0;
        int ans = 1440, las = vals.back() - 1440;
        for(int x: vals) {
            ans = min(ans, x - las);
            las = x;
        }
        return ans;
    }
};
