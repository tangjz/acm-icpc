class Solution {
public:
    int busRapidTransit(int target, int inc, int dec, vector<int>& jump, vector<int>& cost) {
        typedef long long LL;
        int m = jump.size();
        unordered_map<int, LL> dp;
        dp[0] = 0;
        dp[1] = inc;
        function<LL(int)> calc = [&](int x) {
            auto it = dp.find(x);
            if(it != dp.end())
                return it -> second;
            LL ret = (LL)inc * x;
            for(int i = 0; i < m; ++i) {
                int d = jump[i], w = cost[i];
                int L = x - x % d, R = L + d;
                ret = min(ret, calc(L / d) + w + (LL)(x - L) * inc);
                if(x > L)
                    ret = min(ret, calc(R / d) + w + (LL)(R - x) * dec);
            }
            return dp[x] = ret;
        };
        return calc(target) % ((int)1e9 + 7);
    }
};
