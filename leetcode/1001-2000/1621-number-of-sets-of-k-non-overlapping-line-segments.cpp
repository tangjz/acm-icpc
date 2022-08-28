class Solution {
public:
    int numberOfSets(int n, int k) {
        // binom(n + k - 1, k + k)
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = (n + k - 1) % mod;
        vector<int> inv(k + k + 1);
        inv[1] = 1;
        for(int i = 2; i <= k + k; ++i) {
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
            ans = (LL)ans * (n + k - i) % mod * inv[i] % mod;
        }
        return ans;
    }
};
