class Solution {
public:
    string lastSubstring(string s) {
        typedef long long LL;
        const int mod1 = (int)1e9 + 7, mod2 = (int)1e9 + 9;
        const int seed1 = 31, seed2 = 29;
        int n = s.size();
        vector<int> pre1(n + 1), pw1(n + 1);
        pw1[0] = 1;
        for(int i = 1; i <= n; ++i) {
            int x = s[i - 1] - 'a';
            pre1[i] = ((LL)pre1[i - 1] * seed1 + x) % mod1;
            pw1[i] = (LL)pw1[i - 1] * seed1 % mod1;
        }
        auto cmp = [&](int const &u, int const &v) {
            int L = 0, R = n - max(u, v);
            while(L < R) {
                int M = (L + R + 1) >> 1;
                int u1 = (pre1[u + M] - (LL)pre1[u + L] * pw1[M - L]) % mod1;
                u1 < 0 && (u1 += mod1);
                int v1 = (pre1[v + M] - (LL)pre1[v + L] * pw1[M - L]) % mod1;
                v1 < 0 && (v1 += mod1);
                if(u1 == v1) {
                    L = M;
                } else {
                    R = M - 1;
                }
            }
            if(L < n - max(u, v))
                return (s[u + L] > s[v + L]) - (s[u + L] < s[v + L]);
            return (u < v) - (u > v);
        };
        int best = 0;
        for(int i = 1; i < n; ++i)
            if(cmp(best, i) < 0)
                best = i;
        return s.substr(best);
    }
};
