class Solution {
public:
    int maxNiceDivisors(int tot) {
        int cnt3 = tot / 3, cnt2 = 0;
        switch(tot % 3) {
            case 0: {
                break;
            }
            case 1: {
                if(tot > 1) {
                    --cnt3;
                    cnt2 += 2;
                }
                break;
            }
            case 2: {
                ++cnt2;
                break;
            }
        }
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 1;
        for(int x = 3; cnt3 > 0; cnt3 >>= 1, x = (LL)x * x % mod)
            if(cnt3 & 1)
                ans = (LL)ans * x % mod;
        for(int x = 2; cnt2 > 0; cnt2 >>= 1, x = (LL)x * x % mod)
            if(cnt2 & 1)
                ans = (LL)ans * x % mod;
        return ans;
    }
};
