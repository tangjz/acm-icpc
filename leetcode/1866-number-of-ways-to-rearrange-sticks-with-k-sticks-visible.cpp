class Solution {
public:
    int rearrangeSticks(int n, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        vector<int> f(k);
        f[0] = 1;
        for(int i = 1; i < n; ++i)
            for(int j = k - 1; j >= 0; --j)
                f[j] = ((LL)i * f[j] + (j > 0 ? f[j - 1] : 0)) % mod;
        return f[k - 1];
    }
};
