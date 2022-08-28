class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        int ans = 0, n = costs.size(), m = costs[0].size();
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m; ++j) {
                int low = INT_MAX;
                for(int k = 0; k < m; ++k)
                    if(j != k)
                        low = min(low, costs[i - 1][k]);
                costs[i][j] += low;
            }
        return *min_element(costs.back().begin(), costs.back().end());
    }
};
