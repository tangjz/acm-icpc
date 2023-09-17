class Solution {
public:
    long long repairCars(vector<int>& A, int m) {
        typedef long long LL;
        LL L = 0, R = 100LL * m * m;
        while(L < R) {
            LL M = (L + R) >> 1, ctr = 0;
            for(int x: A) {
                LL y = M / x;
                int rt = sqrtl(y);
                for( ; (LL)rt * rt <= y; ++rt);
                for( ; (LL)rt * rt > y; --rt);
                ctr += rt;
            }
            if(ctr >= m) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
