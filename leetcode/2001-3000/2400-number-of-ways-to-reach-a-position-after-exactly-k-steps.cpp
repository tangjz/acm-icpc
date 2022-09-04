class Solution {
public:
    int numberOfWays(int startPos, int endPos, int k) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int dt = abs(endPos - startPos);
        if(k < dt || (k - dt) & 1)
            return 0;
        int ans = 1, L = (k - dt) / 2, R = k - L;
        vector<int> inv(k + 1);
        inv[1] = 1;
        for(int i = 2; i <= k; ++i) {
            inv[i] = mod - (int)(mod / i * (LL)inv[mod % i] % mod);
            ans = (LL)ans * i % mod;
            if(i <= L)
                ans = (LL)ans * inv[i] % mod;
            if(i <= R)
                ans = (LL)ans * inv[i] % mod;
        }
        return ans;
    }
};
