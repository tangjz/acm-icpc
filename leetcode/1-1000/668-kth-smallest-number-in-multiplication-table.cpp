class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        if(m < n)
            swap(m, n);
        int L = 1, R = n * m;
        while(L < R) {
            int M = (L + R) >> 1;
            int cnt = 0;
            for(int i = 1; i <= n; ++i)
                cnt += min(M / i, m);
            if(cnt < k) {
                L = M + 1;
            } else {
                R = M;
            }
        }
        return L;
    }
};
