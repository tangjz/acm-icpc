class Solution {
public:
    int totalStrength(vector<int>& A) {
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int n = A.size(), ans = 0;
        vector<int> pL(n), pR(n), sum1(n + 1), sum2(n + 1);
        for(int i = 0; i < n; ++i) {
            sum1[i + 1] = (sum1[i] + A[i]) % mod;
            sum2[i + 1] = (sum2[i] + (LL)i * A[i]) % mod;
            for(pL[i] = i - 1; pL[i] >= 0 && A[pL[i]] >= A[i]; pL[i] = pL[pL[i]]);
        }
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && A[pR[i]] > A[i]; pR[i] = pR[pR[i]]);
            int sL = ((sum2[i + 1] - sum2[pL[i] + 1]) - (LL)pL[i] * (sum1[i + 1] - sum1[pL[i] + 1])) % mod;
            int sR = ((LL)pR[i] * (sum1[pR[i]] - sum1[i + 1]) - (sum2[pR[i]] - sum2[i + 1])) % mod;
            int prd = ((LL)sL * (pR[i] - i) + (LL)(i - pL[i]) * sR) % mod;
            ans = (ans + (LL)prd * A[i]) % mod;
        }
        return ans < 0 ? ans + mod : ans;
    }
};
