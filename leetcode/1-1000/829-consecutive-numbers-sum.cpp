class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int ans = 0, even = 2;
        for( ; !(n & 1); n >>= 1, even <<= 1);
        for(int i = 1; i * i <= n; ++i) {
            if(n % i > 0)
                continue;
            ++ans;
            if(i * i < n)
                ++ans;
        }
        return ans;
    }
};
