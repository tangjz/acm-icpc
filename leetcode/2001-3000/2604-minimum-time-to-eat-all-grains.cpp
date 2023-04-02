class Solution {
public:
    int minimumTime(vector<int>& A, vector<int>& B) {
        typedef long long LL;
        int n = A.size(), m = B.size();
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        int L = 0, R = (max(A.back(), B.back()) - min(A.front(), B.front())) * 2;
        auto check = [&](int x, int pL, int pR) {
            if(x <= pL)
                return pR - x;
            if(x >= pR)
                return x - pL;
            return pR - pL + min(x - pL, pR - x);
        };
        while(L < R) {
            int M = L + ((R - L) >> 1);
            int las = 0;
            for(int x: A) {
                int cur = las;
                for( ; cur < m && check(x, B[las], B[cur]) <= M; ++cur);
                las = cur;
            }
            if(las == m) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
