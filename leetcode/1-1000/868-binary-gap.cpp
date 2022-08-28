class Solution {
public:
    int binaryGap(int n) {
        int ans = 0;
        n >>= __builtin_ctz(n) + 1;
        while(n > 0) {
            int c = __builtin_ctz(n);
            ans = max(ans, c + 1);
            n >>= c + 1;
        }
        return ans;
    }
};
