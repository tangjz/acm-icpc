class Solution {
public:
    int maxIncreasingGroups(vector<int>& seq) {
        typedef long long LL;
        int n = seq.size(), L = 0, R = n;
        sort(seq.begin(), seq.end());
        while(L < R) {
            int M = (L + R + 1) >> 1;
            LL low = 0, upp = 0;
            for(int i = 1; i <= n; ++i) {
                if(i <= M)
                    upp += M - i + 1;
                low = min(low + seq[n - i], upp);
            }
            if(low == upp) {
                L = M;
            } else {
                R = M - 1;
            }
        }
        return L;
    }
};
