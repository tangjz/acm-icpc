class Solution {
public:
    int numberOfGoodSubarraySplits(vector<int>& A) {
        typedef long long LL;
        static const int mod = (int)1e9 + 7;
        int n = A.size(), las[2] = {-1, -1};
        vector<int> f(n + 1);
        f[0] = 1;
        for(int i = 1; i <= n; ++i) {
            if(A[i - 1]) {
                las[1] = las[0];
                las[0] = i - 1;
            }
            f[i] = f[i - 1];
            if(las[0] >= 0)
                (f[i] += f[las[0]]) >= mod && (f[i] -= mod);
            if(las[1] >= 0)
                (f[i] -= f[las[1]]) < 0 && (f[i] += mod);
        }
        int ans = f[n] - f[n - 1];
        return ans < 0 ? ans + mod : ans;
    }
};
