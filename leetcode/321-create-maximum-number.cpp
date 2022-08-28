class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(), m = nums2.size();
        int k1 = min(n, k), k2 = min(m, k);
        vector<vector<int> > suf1(k1, vector<int>(n)), suf2(k2, vector<int>(m));
        for(int i = 0; i < k1; ++i) {
            int R = n - 1 - i;
            suf1[i][R] = R;
            for(int j = R - 1; j >= 0; --j)
                suf1[i][j] = nums1[j] < nums1[suf1[i][j + 1]] ? suf1[i][j + 1] : j;
        }
        for(int i = 0; i < k2; ++i) {
            int R = m - 1 - i;
            suf2[i][R] = R;
            for(int j = R - 1; j >= 0; --j)
                suf2[i][j] = nums2[j] < nums2[suf2[i][j + 1]] ? suf2[i][j + 1] : j;
        }
        vector<int> ret;
        vector<pair<int, int> > f = {{0, 0}};
        for(int i = 0; i < k; ++i) {
            int mx = -1;
            vector<pair<int, int> > g, h;
            for(auto &it: f) {
                int x, y;
                tie(x, y) = it;
                if(x < n) {
                    int u = suf1[max(k - 1 - i - (m - y), 0)][x];
                    if(mx < nums1[u]) {
                        mx = nums1[u];
                        g.clear();
                        h.clear();
                    }
                    if(mx == nums1[u]) {
                        while(!g.empty() && g.back().first >= u + 1)
                            g.pop_back();
                        g.push_back({u + 1, y});
                    }
                }
                if(y < m) {
                    int v = suf2[max(k - 1 - i - (n - x), 0)][y];
                    if(mx < nums2[v]) {
                        mx = nums2[v];
                        g.clear();
                        h.clear();
                    }
                    if(mx == nums2[v]) {
                        if(h.empty() || h.back().second > v + 1)
                            h.push_back({x, v + 1});
                    }
                }
            }
            f.clear();
            auto it = g.begin(), jt = h.begin();
            while(it != g.end() || jt != h.end()) {
                pair<int, int> cur;
                if(jt == h.end() || (it != g.end() && *it < *jt)) {
                    cur = *(it++);
                } else {
                    cur = *(jt++);
                }
                if(f.empty() || f.back().second > cur.second)
                    f.push_back(cur);
            }
            ret.push_back(mx);
        }
        return ret;
    }
};
