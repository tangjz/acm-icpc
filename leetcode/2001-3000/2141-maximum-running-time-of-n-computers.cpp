class Solution {
public:
    long long maxRunTime(int n, vector<int>& seq) {
        typedef long long LL;
        LL L = 0, R = 0;
        for(int x: seq)
            R += x;
        R /= n;
        while(L < R) {
            LL M = (L + R + 1) >> 1;
            LL ctr = 0;
            for(int x: seq)
                ctr += min((LL)x, M);
            if(ctr >= n * M) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
