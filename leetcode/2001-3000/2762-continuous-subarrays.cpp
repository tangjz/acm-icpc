class Solution {
public:
    long long continuousSubarrays(vector<int>& A) {
        typedef long long LL;
        int n = A.size();
        LL ans = 0;
        vector<int> pL(n), pR(n), qL(n), qR(n);
        for(int i = n - 1; i >= 0; --i) {
            for(pR[i] = i + 1; pR[i] < n && A[i] >= A[pR[i]]; pR[i] = pR[pR[i]]);
            for(qR[i] = i + 1; qR[i] < n && A[i] <= A[qR[i]]; qR[i] = qR[qR[i]]);
        }
        for(int i = 0; i < n; ++i) {
            for(pL[i] = i - 1; pL[i] >= 0 && A[i] >= A[pL[i]]; pL[i] = pL[pL[i]]);
            for(qL[i] = i - 1; qL[i] >= 0 && A[i] < A[qL[i]]; qL[i] = qL[qL[i]]);
            int L = pL[i], R = pR[i];
            for( ; L >= 0 && A[i] + 2 >= A[L]; L = pL[L]);
            for( ; R < n && A[i] + 2 >= A[R]; R = pR[R]);
            L = max(L, qL[i]);
            R = min(R, qR[i]);
            ans += (LL)(i - L) * (R - i);
        }
        return ans;
    }
};
