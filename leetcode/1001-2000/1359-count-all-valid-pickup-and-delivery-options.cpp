class Solution {
public:
    int countOrders(int n) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 1;
        for(int i = 2; i <= n; ++i)
            ans = (LL)ans * i * (i + i - 1) % mod;
        return ans;
    }
};
