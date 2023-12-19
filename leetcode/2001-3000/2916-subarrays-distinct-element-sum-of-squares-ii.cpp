class Solution {
public:
    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, int> las;
        vector<int> pL(n);
        for(int i = 0; i < n; ++i) {
            auto it = las.find(nums[i]);
            if(it == las.end()) {
                pL[i] = -1;
            } else {
                pL[i] = it -> second;
            }
            las[nums[i]] = i;
        }
        typedef long long LL;
        const int mod = (int)1e9 + 7;
        int ans = 0;
        vector<int> s0(n + 1), s1(n + 1);
        auto inc = [&](int x, int v0, int v1) {
            for( ; x <= n; x += x & -x) {
                (s0[x] += v0) >= mod && (s0[x] -= mod);
                (s1[x] += v1) >= mod && (s1[x] -= mod);
            }
        };
        auto ask = [&](int x) {
            int r0 = 0, r1 = 0;
            for( ; x > 0; x -= x & -x) {
                (r0 += s0[x]) >= mod && (r0 -= mod);
                (r1 += s1[x]) >= mod && (r1 -= mod);
            }
            return make_pair(r0, r1);
        };
        for(int i = n - 1; i >= 0; --i) {
            pair<int, int> t0 = ask(pL[i] + 2), t1 = ask(i + 1);
            (t1.first -= t0.first) < 0 && (t1.first += mod);
            (t1.second -= t0.second) < 0 && (t1.second += mod);
            ans = (ans + (LL)(i - pL[i]) * t0.first + (LL)i * t1.first - (LL)t1.second) % mod;
            int v0 = (n - i) % mod, v1 = (LL)v0 * pL[i] % mod;
            v1 < 0 && (v1 += mod);
            inc(pL[i] + 2, v0, v1);
        }
        ans < 0 && (ans += mod);
        // for(int i = 0; i < n; ++i)
        //     for(int j = i + 1; j < n; ++j)
        //         if(pL[j] < i)
        //             ans = (ans + (LL)(i - max(pL[j], pL[i])) * (n - j)) % mod;
        (ans <<= 1) >= mod && (ans -= mod);
        for(int i = 0; i < n; ++i)
            ans = (ans + (LL)(i - pL[i]) * (n - i)) % mod;
        return ans;
        // let L > lft[u] && R >= u && L <= u
        // for u, v:
        //     L > max(lft) && L <= min(u) && R >= max(u)
        //     [lu, u]
        //         [lv, v]
        //     u < v:
        //         lu < lv < u:   ans += (u-lv) * (n-v)
        //         lv <= lu: ans += (u-lu) * (n-v)
    }
};
