class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        typedef long long LL;
        int n = nums.size();
        vector<int> ord(n), bits(n + 1);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return nums[u] < nums[v];
        });
        auto upd = [&](int x, int v) {
            for(++x; x <= n; x += x & -x)
                bits[x] += v;
        };
        auto que = [&](int x) {
            int ret = 0;
            for(++x; x > 0; x -= x & -x)
                ret += bits[x];
            return ret;
        };
        int las = 0;
        LL ans = 0;
        for(int i = 0; i < n; ++i)
            upd(i, 1);
        for(int i = 0; i < n; ++i) {
            int cur = ord[i];
            if(las <= cur) {
                ans += que(cur) - que(las - 1);
            } else {
                ans += que(cur) - que(las - 1) + n - i;
            }
            upd(cur, -1);
            las = cur;
        }
        return ans;
    }
};
