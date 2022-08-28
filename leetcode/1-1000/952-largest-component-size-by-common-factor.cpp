class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size(), m = *max_element(nums.begin(), nums.end()) + 1;
        vector<int> dsu(n, -1), rep(m, -1);
        function<int(int)> dsu_find = [&](int x) -> int {
            return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
        };
        auto dsu_merge = [&](int u, int v) {
            u = dsu_find(u);
            v = dsu_find(v);
            if(u == v)
                return;
            if(dsu[u] < dsu[v])
                swap(u, v);
            dsu[v] += dsu[u];
            dsu[u] = v;
        };
        for(int i = 0; i < n; ++i)
            rep[nums[i]] = i;
        for(int i = 2; i < m; ++i)
            for(int j = i, las = -1; j < m; j += i)
                if(rep[j] != -1) {
                    if(las != -1) {
                        dsu_merge(las, rep[j]);
                    } else {
                        las = rep[j];
                    }
                }
        int ans = 0;
        for(int i = 0; i < n; ++i)
            ans = max(ans, -dsu[i]);
        return ans;
    }
};
