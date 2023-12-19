class Solution {
public:
    long long largestPerimeter(vector<int>& A) {
        typedef long long LL;
        int n = A.size();
        sort(A.begin(), A.end());
        LL ans = -1, sum = A[0] + A[1];
        for(int i = 2; i < n; ++i) {
            if(sum > A[i])
                ans = max(ans, sum + A[i]);
            sum += A[i];
        }
        return ans;
    }
};
