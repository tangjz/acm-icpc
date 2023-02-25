class Solution {
public:
    long long maxPower(vector<int>& a, int r, int k) {
        typedef long long LL;
        int n = a.size();
        vector<int> b(n);
        LL L = 0, R = (LL)2e10;
        while(L < R) {
            LL M = (L + R + 1) >> 1, sum = 0;
            bool bad = 0;
            int rem = k;
            b.assign(a.begin(), a.end());
            for(int i = 0, p = 0, q = 0; i < n; ++i) {
                for( ; q < n && q - i <= r; ++q)
                    sum += b[q];
                for( ; i - p > r; ++p)
                    sum -= b[p];
                LL dt = M - sum;
                if(dt > rem) {
                    bad = 1;
                    break;
                } else if(dt > 0) {
                    sum += dt;
                    b[q - 1] += dt;
                    rem -= dt;
                }
            }
            if(bad) {
                R = M - 1;
            } else {
                L = M;
            }
        }
        return L;
    }
};
