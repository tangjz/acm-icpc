class Solution {
public:
    int getMinimumTime(vector<int>& time, vector<vector<int>>& fruits, int limit) {
        int ans = 0;
        for(auto &it: fruits) {
            int cnt = (it[1] - 1) / limit + 1;
            ans += cnt * time[it[0]];
        }
        return ans;
    }
};
