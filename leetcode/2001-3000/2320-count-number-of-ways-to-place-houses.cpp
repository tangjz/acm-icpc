class Solution {
public:
    int countHousePlacements(int n) {
        const int mod = (int)1e9 + 7;
        int f[2] = {1, 2};
        for(int i = 2; i <= n; ++i)
            f[i & 1] = (f[0] + f[1]) % mod;
        int ans = f[n & 1];
        ans = 1LL * ans * ans % mod;
        return ans;
    }
};
