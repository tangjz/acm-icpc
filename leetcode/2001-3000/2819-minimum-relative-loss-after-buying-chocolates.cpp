class Solution {
public:
    vector<long long> minimumRelativeLosses(vector<int>& A, vector<vector<int>>& queries) {
        // p > ki ? min(2 ki - pi) : min(pi)
        typedef long long LL;
        int n = A.size();
        sort(A.begin(), A.end());
        vector<LL> psum = {0};
        for(int x: A)
            psum.push_back(psum.back() + x);
        vector<LL> ret;
        for(auto &cur: queries) {
            int k = cur[0], m = cur[1];
            int sz = upper_bound(A.begin(), A.end(), k) - A.begin();
            int L = 0, R = min(sz, m);
            while(L < R) {
                int M = (L + R) >> 1;
                int vL = M ? A[M - 1] : INT_MIN;
                int vR = M < m ? k + k - A[n - m + M] : INT_MAX;
                if(vL >= vR) {
                    R = M;
                } else {
                    L = M + 1;
                }
            }
            LL tp = psum[L] + 2LL * k * (m - L) - psum[n] + psum[n - m + L];
            if(L > 0) {
                --L;
                tp = min(tp, psum[L] + 2LL * k * (m - L) - psum[n] + psum[n - m + L]);
            }
            ret.push_back();
        }
        return ret;
    }
};