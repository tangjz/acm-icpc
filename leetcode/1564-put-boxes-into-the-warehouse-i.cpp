class Solution {
public:
    int maxBoxesInWarehouse(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size(), ans = 0;
        sort(A.begin(), A.end());
        for(int i = 1; i < m; ++i)
            B[i] = min(B[i], B[i - 1]);
        reverse(B.begin(), B.end());
        for(int i = 0, j = 0; i < n && j < m; ++i) {
            for( ; j < m && B[j] < A[i]; ++j);
            if(j < m) {
                ++ans;
                ++j;
            }
        }
        return ans;
    }
};
