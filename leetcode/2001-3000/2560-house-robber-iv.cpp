class Solution {
public:
    int minCapability(vector<int>& A, int k) {
        int n = A.size(), L = 0, R = (int)1e9;
        while(L < R) {
            int M = (L + R) / 2;
            int cnt = 0;
            for(int i = 0, j; i < n; ) {
                if(A[i] > M) {
                    ++i;
                    continue;
                }
                for(j = i++; i < n && A[i] <= M; ++i);
                cnt += (i - j + 1) / 2;
            }
            if(cnt >= k) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
