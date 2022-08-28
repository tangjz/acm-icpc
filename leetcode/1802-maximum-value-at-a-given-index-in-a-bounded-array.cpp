class Solution {
    typedef long long LL;
    bool check(int n, int id, LL upp, int val) {
        int pL = max(id - val + 1, 0);
        if((upp -= pL) < 0) // [0, pL)
            return 0;
        int vL = val - id + pL;
        if(pL < id && (upp -= (vL + val - 1LL) * (id - pL) / 2) < 0) // [pL, id)
            return 0;
        int pR = min(id + val - 1, n);
        if((upp -= n - pR) < 0) // [pR, n)
            return 0;
        int vR = val - pR + id;
        if(id < pR && (upp -= (val + vR + 1LL) * (pR - id) / 2) < 0) // [id, pR)
            return 0;
        return 1;
    }
public:
    int maxValue(int n, int index, int maxSum) {
        int L = 1, R = maxSum;
        while(L < R) {
            int M = (L + R + 1) >> 1;
            if(check(n, index, maxSum, M)) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
