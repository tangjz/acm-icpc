class Solution {
public:
    int minProcessingTime(vector<int>& A, vector<int>& B) {
        int n = A.size(), ans = 0;
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        for(int i = 0, j = n * 4 - 1; i < n; ++i, j -= 4)
            ans = max(ans, A[i] + B[j]);
        return ans;
    }
};
