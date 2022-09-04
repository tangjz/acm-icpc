class Solution {
public:
    int matchPlayersAndTrainers(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        int L = 0, R = min(n, m);
        while(L < R) {
            int M = (L + R + 1) >> 1;
            bool bad = 0;
            for(int i = 0; !bad && i < M; ++i)
                bad |= A[i] > B[m - M + i];
            if(bad) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
