class Solution {
public:
    int numberOfWays(string s, string t, long long k) {
        auto minRep = [](string const &s) -> int {
            int i = 0, j = 1, k, l = s.size();
            while(i < l && j < l) {
                for(k = 0; k < l && s[(i + k) % l] == s[(j + k) % l]; ++k);
                if(k == l) return i;
                if(s[(i + k) % l] > s[(j + k) % l])
                    if(i + k + 1 > j) i = i + k + 1;
                    else i = j + 1;
                else if(j + k + 1 > i) j = j + k + 1;
                else j = i + 1;
            }
            return min(i, j);
        };
        auto minPer = [](string const &s) -> int {
            int n = s.size();
            vector<int> f(n + 1);
            f[0] = f[1] = 0;
            for(int i = 1, j = 0; i < n; ++i) {
                while(j && s[i] != s[j]) j = f[j];
                f[i + 1] = s[i] == s[j] ? ++j : 0;
            }
            return n % (n - f[n]) > 0 ? n : n - f[n];
        };
        int u = minRep(s), v = minRep(t);
        rotate(s.begin(), s.begin() + u, s.end());
        rotate(t.begin(), t.begin() + v, t.end());
        if(s != t)
            return 0;
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        function<int(int)> modInv = [&](int x) {
            return x <= 1 ? x : mod - (int)(mod / x * (LL)modInv(mod % x) % mod);
        };
        auto modPow = [&](int x, LL k) {
            int ret = 1;
            for( ; k > 0; k >>= 1, x = (LL)x * x % mod)
                if(k & 1)
                    ret = (LL)ret * x % mod;
            return ret;
        };
        int n = s.size(), p = minPer(s);
        int ans = ((LL)(modPow(n - 1, k) + (k & 1 ? 1 : -1)) * modInv(p) + ((u - v) % p == 0 ? (k & 1 ? -1 : 1) : 0)) % mod;
        return ans < 0 ? ans + mod : ans;
    }
};
