class Solution {
public:
    int numberOf2sInRange(int n) {
        int ans = 0, pw = 1;
        for( ; pw + pw <= n; pw *= 10) {
            int hi = n / pw / 10;
            if(hi > 0)
                ans += hi * pw;
            hi = (hi * 10 + 2) * pw;
            if(hi <= n)
                ans += min(hi + pw - 1, n) - hi + 1;
            // printf("pw %d hi %d %d ans %d\n", pw, n / pw / 10, hi, ans);
        }
        return ans;
    }
};
