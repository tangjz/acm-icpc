class Solution {
public:
    int minOperations(vector<int>& nums, int v) {
        typedef long long LL;
        static const int maxl = 31;
        static int mx = 0, ctr[maxl];
        LL upp = 0;
        memset(ctr, 0, sizeof ctr);
        for(int x: nums) {
            int y = __builtin_ctz(x);
            mx = max(mx, y);
            ++ctr[y];
            upp += x;
        }
        if(upp < v)
            return -1;
        int ans = 0;
        for(int i = 0; i <= mx; ++i) {
            // printf("chk %d:", i);
            // for(int j = 0; j < i; ++j)
            //     printf(" %d", ctr[j]);
            // printf(" %lld\n", upp);
            int rem = v, tmp = min((LL)(rem >> i), upp);
            rem -= tmp << i;
            for(int j = i - 1; rem > 0 && j >= 0; --j) {
                tmp = min(rem >> j, ctr[j]);
                rem -= tmp << j;
            }
            if(rem > 0) {
                // printf("failed %d: %d\n", i, rem);
                int j = i;
                for( ; j <= mx && !ctr[j]; ++j);
                assert(j <= mx);
                for( ; j >= i; --j) {
                    --ctr[j];
                    ctr[j - 1] += 2;
                    ++ans;
                }
                --upp;
            }
            upp = (upp - ctr[i]) >> 1;
        }
        return ans;
    }
};
