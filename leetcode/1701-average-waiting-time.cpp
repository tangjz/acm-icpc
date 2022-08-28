class Solution {
public:
    double averageWaitingTime(vector<vector<int>>& customers) {
        int cur = 0;
        double ans = 0;
        for(auto const &it : customers) {
            cur = max(cur, it[0]) + it[1];
            ans += cur - it[0];
        }
        return ans / (int)customers.size();
    }
};
