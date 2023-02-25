class Solution {
public:
    int monkeyMove(int n) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 1, pw = 2;
        for( ; n > 0; n >>= 1, pw = (LL)pw * pw % mod)
            if(n & 1)
                ans = (LL)ans * pw % mod;
        (ans -= 2) < 0 && (ans += mod);
        return ans;
    }
};
