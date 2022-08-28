class Solution {
public:
    string longestDupSubstring(string s) {
        typedef long long LL;
        const int mod = (int)1e9 + 7, mod2 = (int)1e9 + 9, seed = 61;
        int n = s.size();
        vector<int> hs(n + 1), pw(n + 1);
        vector<int> hs2(n + 1), pw2(n + 1);
        pw[0] = pw2[0] = 1;
        for(int i = 0; i < n; ++i) {
            int o = s[i] - 'a';
            hs[i + 1] = ((LL)hs[i] * seed + o) % mod;
            pw[i + 1] = (LL)pw[i] * seed % mod;
            hs2[i + 1] = ((LL)hs2[i] * seed + o) % mod2;
            pw2[i + 1] = (LL)pw2[i] * seed % mod2;
        }
        int L = 0, R = n - 1;
        string ret = "";
        while(L < R) {
            int M = (L + R + 1) >> 1;
            string tmp = "";
            unordered_set<LL> vis;
            vis.reserve(n);
            for(int i = 0; i <= n - M; ++i) {
                int hh = (hs[i + M] - (LL)hs[i] * pw[M]) % mod;
                hh < 0 && (hh += mod);
                int hh2 = (hs2[i + M] - (LL)hs2[i] * pw2[M]) % mod2;
                hh2 < 0 && (hh2 += mod2);
                if(!vis.insert((LL)hh << 32 | hh2).second) {
                    tmp = s.substr(i, M);
                    break;
                }
            }
            if(tmp != "") {
                ret = tmp;
                L = M;
            } else {
                R = M - 1;
            }
        }
        return ret;
    }
};
