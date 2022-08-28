class Solution {
public:
    int minNumberOfHours(int sA, int sB, vector<int>& A, vector<int>& B) {
        int n = A.size(), cA = 1, cB = 0, pB = 0;
        for(int i = 0; i < n; ++i) {
            cA += A[i];
            cB = max(cB, B[i] - pB + 1);
            pB += B[i];
        }
        return max(cA - sA, 0) + max(cB - sB, 0);
    }
};
