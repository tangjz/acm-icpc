class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [&](auto const &it, auto const &jt) {
            return it[1] - it[0] > jt[1] - jt[0];
        });
        int ans = 0, pre = 0;
        for(auto &it: tasks) {
            ans = max(ans, pre + it[1]);
            pre += it[0];
        }
        return ans;
    }
};
