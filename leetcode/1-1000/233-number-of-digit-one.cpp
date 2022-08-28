class Solution {
public:
    int countDigitOne(int n) {
        int ans = 0;
        for(long long pw = 1; pw <= n; pw *= 10) {
            int hi = n / pw / 10;
            if(hi > 0)
                ans += hi * pw;
            hi = (hi * 10 + 1) * pw;
            if(hi <= n)
                ans += min(hi + pw - 1, (long long)n) - hi + 1;
            // printf("pw %d hi %d %d ans %d\n", pw, n / pw / 10, hi, ans);
        }
        return ans;
    }
};
