class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size(), ans = INT_MIN;
        vector<int> f(n), g(n);
        for(int i = n - 1; i >= 0; --i) {
            f[i] = (i + 1 < n ? max(f[i + 1], 0) : 0) + arr[i];
            g[i] = i + 1 < n ? max(g[i + 1], f[i]) : f[i];
        }
        int pf = 0, pg = INT_MIN;
        for(int i = 0; i < n; ++i) {
            ans = max(ans, pf + f[i]);
            ans = max(ans, i + 1 < n ? max(pg, max(pf + f[i + 1], g[i + 1])) : pg);
            pg = max(pg, pf + arr[i]);
            pf = max(pf + arr[i], 0);
        }
        return ans;
    }
};
