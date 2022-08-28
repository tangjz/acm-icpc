class Solution {
public:
    bool findGameWinner(int n) {
        int f[2] = {1, 0};
        for(int i = 2; i <= n; ++i)
            f[i & 1] = (f[0] + 1) ^ (f[1] + 1);
        return f[n & 1];
    }
};
