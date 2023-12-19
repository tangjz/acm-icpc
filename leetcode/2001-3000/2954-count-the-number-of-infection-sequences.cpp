class Solution {
public:
    int numberOfSequence(int n, vector<int>& p) {
        typedef long long LL;
        static const int maxn = (int)1e5 + 1, mod = (int)1e9 + 7;
        static int fact[maxn] = {}, iact[maxn];
        if(!fact[0]) {
            iact[1] = 1;
            for(int i = 2; i < maxn; ++i)
                iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
            fact[0] = iact[0] = 1;
            for(int i = 1; i < maxn; ++i) {
                fact[i] = (LL)fact[i - 1] * i % mod;
                iact[i] = (LL)iact[i - 1] * iact[i] % mod;
            }
        }
        int m = p.size(), ans = fact[n - m];
        if(p[0] > 0)
            ans = (LL)ans * iact[p[0]] % mod;
        if(p[m - 1] < n - 1)
            ans = (LL)ans * iact[n - 1 - p[m - 1]] % mod;
        for(int i = 1; i < m; ++i) {
            if(p[i] == p[i - 1] + 1)
                continue;
            int tmp = 0;
            for(int j = p[i - 1] + 1; j < p[i]; ++j)
                tmp = (tmp + (LL)iact[j - p[i - 1] - 1] * iact[p[i] - 1- j]) % mod;
            tmp = (LL)tmp * fact[p[i] - p[i - 1] - 2] % mod * iact[p[i] - p[i - 1] - 1] % mod;
            // printf("L %d R %d tmp %d\n", p[i - 1], p[i], tmp);

            ans = (LL)ans * tmp % mod;
        }
        return ans;
    }
};
