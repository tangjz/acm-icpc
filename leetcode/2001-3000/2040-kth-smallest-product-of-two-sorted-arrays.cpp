class Solution {
public:
    long long kthSmallestProduct(vector<int>& A, vector<int>& B, long long k) {
        typedef long long LL;
        int n = A.size(), m = B.size();
        vector<LL> cand;
        for(int x: {A.front(), A.back()})
            for(int y: {B.front(), B.back()})
                cand.push_back((LL)x * y);
        sort(cand.begin(), cand.end());
        LL L = cand.front(), R = cand.back();
        int cA = 0, pA = -1, qA = n;
        int cB = 0, pB = -1, qB = m;
        for(int i = 0; i < n; ++i) {
            if(A[i] < 0) {
                pA = i;
            } else if(A[i] > 0) {
                qA = min(qA, i);
            } else {
                ++cA;
            }
        }
        for(int i = 0; i < m; ++i) {
            if(B[i] < 0) {
                pB = i;
            } else if(B[i] > 0) {
                qB = min(qB, i);
            } else {
                ++cB;
            }
        }
        while(L < R) {
            LL M = (L + R) >> 1; // prd <= M
            LL ctr = 0;
            // neg
            for(int i = qB, j = 0; i < m && j <= pA; ++i) {
                while(j < pA && (LL)B[i] * A[j + 1] <= M)
                    ++j;
                if((LL)B[i] * A[j] <= M)
                    ctr += j + 1;
            }
            for(int i = qA, j = 0; i < n && j <= pB; ++i) {
                while(j < pB && (LL)A[i] * B[j + 1] <= M)
                    ++j;
                if((LL)A[i] * B[j] <= M)
                    ctr += j + 1;
            }
            // LL rl = 0;
            // for(int i = 0; i < n; ++i)
            //     for(int j = 0; j < m; ++j)
            //         rl += (LL)A[i] * B[j] <= min(M, -1LL);
            // printf("<= %lld: neg %lld %lld\n", M, ctr, rl);
            // zero
            if(M >= 0)
                ctr += (LL)cA * m + (LL)n * cB - (LL)cA * cB;
            // rl = 0;
            // for(int i = 0; i < n; ++i)
            //     for(int j = 0; j < m; ++j)
            //         rl += (LL)A[i] * B[j] <= min(M, 0LL);
            // printf("<= %lld: neg+zero %lld %lld\n", M, ctr, rl);
            // pos
            for(int i = 0, j = pB; i <= pA && j >= 0; ++i) {
                while(j > 0 && (LL)A[i] * B[j - 1] <= M)
                    --j;
                if((LL)A[i] * B[j] <= M)
                    ctr += pB - j + 1;
            }
            for(int i = n - 1, j = qB; i >= qA && j < m; --i) {
                while(j + 1 < m && (LL)A[i] * B[j + 1] <= M)
                    ++j;
                if((LL)A[i] * B[j] <= M)
                    ctr += j - qB + 1;
            }
            // rl = 0;
            // for(int i = 0; i < n; ++i)
            //     for(int j = 0; j < m; ++j)
            //         rl += (LL)A[i] * B[j] <= M;
            // printf("<= %lld: neg+zero+pos %lld %lld\n", M, ctr, rl);
            if(ctr >= k) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
