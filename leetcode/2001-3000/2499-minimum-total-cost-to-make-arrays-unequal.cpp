class Solution {
public:
    long long minimumTotalCost(vector<int>& A, vector<int>& B) {
        typedef long long LL;
        int n = A.size(), m = 0, mx = 0, p = -1;
        LL ans = 0;
        vector<int> ctr(n + 1);
        for(int i = 0; i < n; ++i) {
            if(A[i] != B[i])
                continue;
            ans += i;
            ++m;
            if(mx < (++ctr[A[i]])) {
                mx = ctr[A[i]];
                p = A[i];
            }
        }
        for(int i = 0; m - mx < mx && i < n; ++i) {
            if(A[i] == B[i] || A[i] == p || B[i] == p)
                continue;
            ans += i;
            ++m;
        }
        return m - mx < mx ? -1 : ans;
    }
};
