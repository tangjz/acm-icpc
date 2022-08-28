class Solution {
public:
    int tribonacci(int n) {
        int f[3] = {0, 1, 1};
        for(int i = 3; i <= n; ++i) {
            f[i % 3] = f[0] + f[1] + f[2];
        }
        return f[n % 3];
    }
};
