class Solution {
public:
    int trailingZeroes(int n) {
        int ans = 0;
        for( ; n >= 5; ans += (n /= 5));
        return ans;
    }
};
