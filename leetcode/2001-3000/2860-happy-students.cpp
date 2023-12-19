class Solution {
public:
    int countWays(vector<int>& A) {
        int n = A.size(), ans = 0;
        sort(A.begin(), A.end());
        for(int i = 0; i < n; ) {
            ans += (!i || i > A[i - 1]) && i < A[i];
            for(int v = A[i]; i < n && A[i] == v; ++i);
        }
        ans += n > A[n - 1];
        return ans;
    }
};
