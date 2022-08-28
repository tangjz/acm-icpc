class Solution {
public:
    vector<long long> minimumCosts(vector<int>& regular, vector<int>& express, int expressCost) {
        typedef long long LL;
        int n = regular.size();
        vector<LL> f(n + 1, LLONG_MAX), g(n + 1, LLONG_MAX);
        f[0] = 0;
        g[0] = expressCost;
        for(int i = 1; i <= n; ++i) {
            f[i] = f[i - 1] + regular[i - 1];
            g[i] = min(g[i - 1] + express[i - 1], f[i] + expressCost);
            f[i] = min(f[i], g[i]);
        }
        f.erase(f.begin());
        return f;
    }
};
