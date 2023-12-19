class Solution {
public:
    int findMaximumLength(vector<int>& A) {
        typedef long long LL;
        int ans = 0, n = A.size(), L = 0;
        vector<int> f(n + 1), que = {0};
        vector<LL> s(n + 1), g(n + 1);
        auto eval = [&](int u) {
            return s[u] + g[u];
        };
        for(int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + A[i - 1];
            for( ; L + 1 < que.size() && eval(que[L + 1]) <= s[i]; ++L);
            f[i] = f[que[L]] + 1;
            g[i] = s[i] - s[que[L]];
            for( ; L < que.size() && eval(que.back()) >= eval(i); que.pop_back());
            que.push_back(i);
        }
        return f[n];
    }
};
