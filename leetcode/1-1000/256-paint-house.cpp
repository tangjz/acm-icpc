class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int ans = 0, n = costs.size();
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < 3; ++j) {
                int low = INT_MAX;
                for(int k = 0; k < 3; ++k)
                    if(j != k)
                        low = min(low, costs[i - 1][k]);
                costs[i][j] += low;
            }
        return *min_element(costs.back().begin(), costs.back().end());
    }
};
