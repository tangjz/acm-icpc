class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = (int)arr.size();
        vector<int> pL(n, 0), pR(n, 0), ord;
        for(int i = 0; i < n; ++i) {
            ord.push_back(i);
            for(pL[i] = i - 1; pL[i] >= 0 && arr[pL[i]] <= arr[i]; pL[i] = pL[pL[i]]);
        }
        for(int i = n - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < n && arr[pR[i]] <= arr[i]; pR[i] = pR[pR[i]]);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return arr[u] < arr[v];
        });
        int ret = 1;
        vector<int> dp(n, 1);
        for(int i = n - 1; i >= 0; --i) {
            int u = ord[i];
            if(pL[u] >= 0 && u - pL[u] <= d)
                dp[u] = max(dp[u], dp[pL[u]] + 1);
            if(pR[u] < n && pR[u] - u <= d)
                dp[u] = max(dp[u], dp[pR[u]] + 1);
            ret = max(ret, dp[u]);
        }
        return ret;
    }
};
