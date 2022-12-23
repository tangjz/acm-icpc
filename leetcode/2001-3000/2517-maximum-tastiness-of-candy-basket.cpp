class Solution {
public:
    int maximumTastiness(vector<int>& A, int k) {
        int n = A.size();
        sort(A.begin(), A.end());
        int L = 0, R = A[n - 1] - A[0];
        while(L < R) {
            int M = (L + R + 1) >> 1, las = -M, cnt = 0;
            for(int x: A)
                if(x - las >= M) {
                    las = x;
                    if((++cnt) >= k)
                        break;
                }
            if(cnt >= k) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
