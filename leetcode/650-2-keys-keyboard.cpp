class Solution {
public:
    int minSteps(int n) {
        int ans = 0;
        for(int i = 2; i <= n; ++i) {
            if(i * i > n)
                i = n;
            while(n % i == 0) {
                ans += i;
                n /= i;
            }
        }
        return ans;
    }
};
