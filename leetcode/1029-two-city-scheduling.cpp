class Solution {
public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        int n = costs.size(), ans = 0;
        for(int i = 0; i < n; ++i) {
            ans += costs[i][1];
            costs[i][0] -= costs[i][1];
        }
        n >>= 1;
        nth_element(costs.begin(), costs.begin() + n, costs.end());
        for(int i = 0; i < n; ++i)
            ans += costs[i][0];
        return ans;
    }
};
