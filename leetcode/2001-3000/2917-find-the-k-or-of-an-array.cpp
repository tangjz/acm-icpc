class Solution {
public:
    int findKOr(vector<int>& A, int k) {
        static const int maxd = 31;
        static int ctr[maxd];
        memset(ctr, 0, sizeof ctr);
        for(int x: A)
            for(int i = 0; x > 0; ++i, x >>= 1)
                if(x & 1)
                    ++ctr[i];
        int ans = 0;
        for(int i = maxd - 1; i >= 0; --i)
            ans = (ans << 1) | (ctr[i] >= k);
        return ans;
    }
};
