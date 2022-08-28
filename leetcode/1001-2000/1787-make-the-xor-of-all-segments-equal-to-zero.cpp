class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        int n = (int)nums.size(), m = 0;
        for(int x: nums) {
            for( ; x >= (1 << m); ++m);
        }
        int all = 1 << m, adt = 0, best = n;
        vector<int> f(all, n);
        f[0] = 0;
        for(int i = 0; i < k; ++i) {
            int tot = 0;
            unordered_map<int, int> ctr;
            for(int j = i; j < n; j += k) {
                ++tot;
                ++ctr[nums[j]];
            }
            int low = n;
            vector<int> g(all, n);
            for(auto &it: ctr) {
                int val = it.first;
                int cost = tot - it.second;
                low = min(low, cost);
                for(int j = 0; j < all; ++j)
                    g[j] = min(g[j], f[j ^ val] + cost);
            }
            adt += low;
            best = min(best, tot - low);
            f = move(g);
        }
        return min(f[0], adt + best);
    }
};
