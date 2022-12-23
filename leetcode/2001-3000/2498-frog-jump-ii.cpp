class Solution {
public:
    int maxJump(vector<int>& A) {
        int n = A.size(), ans = n > 2 ? 0 : A[n - 1] - A[0];
        for(int i = 2; i < n; ++i)
            ans = max(ans, A[i] - A[i - 2]);
        return ans;
    }
};
