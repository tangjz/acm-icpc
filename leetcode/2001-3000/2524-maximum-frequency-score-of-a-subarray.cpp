class Solution {
public:
    int maxFrequencyScore(vector<int>& nums, int k) {
        typedef long long LL;
        static const int maxv = (int)1e6 + 1, mod = (int)1e9 + 7;
        static int inv[maxv];
        inv[1] = 1;
        function<int(int)> getInv = [&](int x) -> int {
            if(!inv[x])
                inv[x] = mod - (int)(mod / x * (LL)getInv(mod % x) % mod);
            return inv[x];
        };
        int ans = 0, sum = 0, n = nums.size();
        unordered_map<int, pair<int, int> > prd;
        auto upd = [&](int x, int v) {
            int w = v > 0 ? x : getInv(x);
            auto it = prd.find(x);
            if(it != prd.end()) {
                (sum -= (it -> second).first) < 0 && (sum += mod);
            } else {
                it = prd.insert({x, {1, 0}}).first;
            }
            if(!((it -> second).second += v)) {
                prd.erase(x);
                return;
            }
            (sum += ((it -> second).first = (LL)(it -> second).first * w % mod)) >= mod && (sum -= mod);
        };
        for(int i = 0; i < n; ++i) {
            upd(nums[i], 1);
            if(i >= k - 1) {
                ans = max(ans, sum);
                upd(nums[i - k + 1], -1);
            }
        }
        return ans;
    }
};
