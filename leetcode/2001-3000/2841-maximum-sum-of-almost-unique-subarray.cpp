class Solution {
public:
    long long maxSum(vector<int>& A, int m, int k) {
        typedef long long LL;
        int n = A.size();
        LL ans = 0, sum = 0;
        unordered_map<int, int> ctr;
        for(int i = 0; i < n; ++i) {
            sum += A[i];
            ++ctr[A[i]];
            if(i >= k - 1) {
                if(ctr.size() >= m)
                    ans = max(ans, sum);
                sum -= A[i - k + 1];
                if(!(--ctr[A[i - k + 1]]))
                    ctr.erase(A[i - k + 1]);
            }
        }
        return ans;
    }
};
