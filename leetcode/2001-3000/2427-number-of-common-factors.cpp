class Solution {
public:
    int commonFactors(int a, int b) {
        int ans = 0;
        for(int i = 1; i <= a && i <= b; ++i)
            ans += a % i == 0 && b % i == 0;
        return ans;
    }
};
