class Solution {
public:
    int maximumScore(vector<int>& A, int k) {
        static const int maxv = (int)1e5 + 1;
        static int tot = 0, pr[maxv], d[maxv] = {}, f[maxv] = {};
        if(!tot) {
            d[1] = 1;
            f[1] = 0;
            for(int i = 2; i < maxv; ++i) {
                if(!d[i]) {
                    pr[tot++] = d[i] = i;
                    f[i] = 1;
                }
                for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
                    d[k] = pr[j];
                    if(d[i] == pr[j]) {
                        f[k] = f[i];
                        break;
                    }
                    f[k] = f[i] + 1;
                }
            }
        }
        int n = A.size();
        vector<int> B(n), pL(n), pR(n), ord(n);
        for(int i = 0; i < n; ++i) {
            B[i] = f[A[i]];
            ord[i] = i;
            for(pL[i] = i - 1; pL[i] >= 0 && B[pL[i]] < B[i]; pL[i] = pL[pL[i]]);
        }
        for(int i = n - 1; i >= 0; --i)
            for(pR[i] = i + 1; pR[i] < n && B[pR[i]] <= B[i]; pR[i] = pR[pR[i]]);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return A[u] < A[v];
        });
        typedef long long LL;
        static const int mod = (int)1e9 + 7;
        int ans = 1;
        while(k > 0 && !ord.empty()) {
            int u = ord.back();
            ord.pop_back();
            LL ways = (LL)(u - pL[u]) * (pR[u] - u);
            ways = min(ways, (LL)k);
            k -= ways;
            for(int x = A[u]; ways > 0; ways >>= 1, x = (LL)x * x % mod)
                if(ways & 1)
                    ans = (LL)ans * x % mod;
        }
        return ans;
    }
};
