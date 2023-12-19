class Solution {
public:
    int incremovableSubarrayCount(vector<int>& A) {
        typedef long long LL;
        int n = A.size(), L = 1;
        LL ans = 0;
        for( ; L < n && A[L - 1] < A[L]; ++L);
        for(int R = n - 1; R >= 0; --R) {
            if(R + 2 < n && A[R + 1] >= A[R + 2])
                break;
            int v = R + 1 < n ? A[R + 1] : INT_MAX;
            for(L = min(L, R); L > 0 && A[L - 1] >= v; --L);
            // printf("R %d L %d\n", R, L);
            ans += L + 1;
        }
        return ans;
    }
};
