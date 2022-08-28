class Solution {
public:
    int waysToStep(int n) {
        const int mod = (int)1e9 + 7;
        int f[3] = {1};
        for(int i = 1, j = 1; i <= n; ++i, (++j) == 3 && (j = 0)) {
            j != 0 && (f[j] += f[0]) >= mod && (f[j] -= mod);
            j != 1 && (f[j] += f[1]) >= mod && (f[j] -= mod);
            j != 2 && (f[j] += f[2]) >= mod && (f[j] -= mod);
        }
        return f[n % 3];
    }
};
