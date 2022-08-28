class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& A, int lim) {
        int n = A.size(), ans = 0;
        sort(A.begin(), A.end());
        for(int i = 0, j = 0, c = 0; i < n; ++i) {
            c += A[i][1] - A[i][0] + 1;
            int lft = A[i][1] - lim + 1;
            for( ; j <= i && lft > A[j][0]; c -= A[j][1] - A[j][0] + 1, ++j);
            ans = max(ans, c + (j > 0 && lft <= A[j - 1][1] ? A[j - 1][1] - lft + 1 : 0));
        }
        for(int i = n - 1, j = n - 1, c = 0; i >= 0; --i) {
            c += A[i][1] - A[i][0] + 1;
            int rht = A[i][0] + lim - 1;
            for( ; j >= i && rht < A[j][1]; c -= A[j][1] - A[j][0] + 1, --j);
            ans = max(ans, c + (j + 1 < n && rht >= A[j + 1][0] ? rht - A[j + 1][0] + 1 : 0));
        }
        return ans;
    }
};
