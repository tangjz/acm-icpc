class Solution {
public:
    int minimizedMaximum(int n, vector<int>& seq) {
        int m = seq.size();
        int L = 1, R = (int)1e5;
        while(L < R) {
            int M = (L + R) >> 1;
            long long ctr = 0;
            for(int x: seq) {
                ctr += (x - 1) / M + 1;
            }
            if(ctr <= n) {
                R = M;
            } else {
                L = M + 1;
            }
        }
        return L;
    }
};
