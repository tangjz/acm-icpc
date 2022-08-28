class Solution {
public:
    int minimumSwitchingTimes(vector<vector<int>>& source, vector<vector<int>>& target) {
        unordered_map<int, int> ctr;
        for(auto &it: source)
            for(int x: it)
                ++ctr[x];
        for(auto &it: target)
            for(int x: it)
                --ctr[x];
        int ans = 0;
        for(auto &it: ctr)
            ans += abs(it.second);
        return (ans + 1) >> 1;
    }
};
