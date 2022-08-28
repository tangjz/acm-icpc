class Solution {
    typedef long long LL;
    struct HT {
        static constexpr int mod[2] = {(int)1e9 + 7, (int)1e9 + 9};
        static constexpr int seed[2] = {31, 29};
        static vector<int> pw[2];
        int len;
        vector<int> hs[2];
        void parse(string const &t) {
            len = t.size();
            while(len >= pw[0].size()) {
                pw[0].push_back((LL)pw[0].back() * seed[0] % mod[0]);
                // pw[1].push_back((LL)pw[1].back() * seed[1] % mod[1]);
            }
            hs[0] = {0};
            hs[1] = {0};
            for(int i = 0; i < len; ++i) {
                int o = t[i] - 'a' + 1;
                hs[0].push_back(((LL)hs[0].back() * seed[0] + o) % mod[0]);
                // hs[1].push_back(((LL)hs[1].back() * seed[1] + o) % mod[1]);
            }
        }
        LL get(int L, int R) {
            int dt = R - L + 1;
            if(!dt)
                return 0;
            int h0 = (hs[0][R + 1] - (LL)hs[0][L] * pw[0][dt]) % mod[0];
            // int h1 = (hs[1][R + 1] - (LL)hs[1][L] * pw[1][dt]) % mod[1];
            // return (LL)(h0 < 0 ? h0 + mod[0] : h0) << 32 | (h1 < 0 ? h1 + mod[1] : h1);
            return h0 < 0 ? h0 + mod[0] : h0;
        }
    };
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        int n = words.size();
        vector<string> rev(n);
        vector<HT> pre(n), suf(n);
        map<LL, int> pH, sH;
        for(int i = 0; i < n; ++i) {
            int len = words[i].size();
            rev[i] = words[i];
            reverse(rev[i].begin(), rev[i].end());
            pre[i].parse(words[i]);
            suf[i].parse(rev[i]);
            pH[pre[i].get(0, len - 1)] = i;
            sH[suf[i].get(0, len - 1)] = i;
        }
        vector<vector<int> > ret;
        for(int i = 0; i < n; ++i) {
            int len = words[i].size();
            for(int j = 0; j <= len; ++j) {
                if(pre[i].get(0, j - 1) == suf[i].get(len - j, len - 1)) {
                    auto it = sH.find(pre[i].get(j, len - 1));
                    if(it != sH.end() && it -> second != i && (j || i < it -> second))
                        ret.push_back({it -> second, i});
                }
                if(suf[i].get(0, j - 1) == pre[i].get(len - j, len - 1)) {
                    auto it = pH.find(suf[i].get(j, len - 1));
                    if(it != pH.end() && it -> second != i && (j || i < it -> second))
                        ret.push_back({i, it -> second});
                }
            }
        }
        return ret;
    }
};

vector<int> Solution::HT::pw[2] = {{1}, {1}};
