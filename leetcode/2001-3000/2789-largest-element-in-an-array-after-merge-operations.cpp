class Solution {
public:
    long long maxArrayValue(vector<int>& A) {
        typedef long long LL;
        int n = A.size();
        LL ans = 0;
        for(int i = n - 1; i >= 0; ) {
            LL tmp = A[i];
            for(--i; i >= 0 && A[i] <= tmp; --i)
                tmp += A[i];
            ans = max(ans, tmp);
        }
        return ans;
    }
};
