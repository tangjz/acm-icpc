class Solution {
public:
    long long coutPairs(vector<int>& nums, int k) {
        typedef long long LL;
        vector<int> f(k + 1);
        for(int &x: nums)
            ++f[gcd(k, x)];
        LL ans = 0;
        for(int i = 1; i <= k; ++i) {
            if(!f[i])
                continue;
            if((LL)i * i % k == 0) {
                ans += f[i] * (f[i] - 1LL) / 2;
            }
            for(int d = k / i, j = d; j < i; j += d)
                ans += (LL)f[i] * f[j];
        }
        return ans;
    }
};
