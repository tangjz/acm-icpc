class Solution {
public:
    typedef long long LL;
    int rangeBitwiseAnd(int m, int n) {
        int ans = 0;
        for(int i = 0; (1LL << i) <= m; ++i)
            if((m >> i) & 1) {
                LL nxt = (m >> i) << i;
                nxt += 1 << i;
                if(nxt > n)
                    ans |= 1 << i;
            }
        return ans;
    }
};
