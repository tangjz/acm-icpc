class Solution {
public:
    int countSubranges(vector<int>& nums1, vector<int>& nums2) {
        const int mod = (int)1e9 + 7;
        int n = nums1.size(), ans = 0;
        vector<pair<int, int> > f, g, h;
        for(int i = 0; i < n; ++i) {
            auto it = lower_bound(f.begin(), f.end(), make_pair(0, 0));
            if(it == f.end() || it -> first != 0) {
                f.insert(it, {0, 1});
            } else {
                (++(it -> second)) >= mod && (it -> second -= mod);
            }
            g.clear();
            h.clear();
            for(auto &it: f) {
                g.push_back({it.first + nums1[i], it.second});
                h.push_back({it.first - nums2[i], it.second});
            }
            f.clear();
            for(auto jt = g.begin(), kt = h.begin(); jt != g.end() || kt != h.end(); ) {
                int val = INT_MAX, ways = 0;
                if(jt != g.end() && val > jt -> first)
                    val = jt -> first;
                if(kt != h.end() && val > kt -> first)
                    val = kt -> first;
                if(jt != g.end() && val == jt -> first)
                    (ways += (jt++) -> second) >= mod && (ways -= mod);
                if(kt != h.end() && val == kt -> first)
                    (ways += (kt++) -> second) >= mod && (ways -= mod);
                f.push_back({val, ways});
                !val && (ans += ways) >= mod && (ans -= mod);
            }
        }
        return ans;
    }
};
