class Solution {
public:
    int fillCups(vector<int>& A) {
        int ans = A[0] + A[1] + A[2];
        for(int i = 0; i <= A[0] && i <= A[1]; ++i)
            for(int j = 0; i + j <= A[0] && j <= A[2]; ++j) {
                int k = min(A[1] - i, A[2] - j);
                ans = min(ans, A[0] + A[1] + A[2] - i - j - k);
            }
        return ans;
    }
};
