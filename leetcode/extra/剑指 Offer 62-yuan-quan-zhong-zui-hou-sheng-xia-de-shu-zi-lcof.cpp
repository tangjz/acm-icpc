class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = 0;
        for(int i = 1; i <= n; ++i)
            ans = (ans + m) % i;
        return ans;
    }
};
