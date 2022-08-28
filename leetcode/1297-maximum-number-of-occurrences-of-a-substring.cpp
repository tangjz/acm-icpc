class Solution {
    struct Hash {
        typedef long long LL;
        int mod, seed;
        vector<int> pw, hh;
        Hash(int m, int s) : mod(m), seed(s), pw({1}), hh({0}) {}
        void parse(string const &s) {
            pw.reserve(s.size() + 1);
            hh.reserve(s.size() + 1);
            while(pw.size() <= s.size())
                pw.push_back((LL)pw.back() * seed % mod);
            hh.resize(1);
            for(char ch : s) {
                int o = ch - 'a' + 1;
                hh.push_back(((LL)hh.back() * seed + o) % mod);
            }
        }
        int get(int L, int R) {
            int ret = (hh[R + 1] - (LL)hh[L] * pw[R - L + 1]) % mod;
            return ret < 0 ? (ret + mod) : ret;
        }
    } ;
public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        const int mod0 = (int)1e9 + 7, seed0 = 37;
        const int mod1 = (int)1e9 + 403, seed1 = 29;
        int len = (int)s.size();
        Hash h0(mod0, seed0), h1(mod1, seed1);
        h0.parse(s);
        h1.parse(s);
        int ret = 0;
        for(int i = minSize; i <= minSize; ++i) {
            const int maxd = 26;
            int tot = 0;
            vector<int> ctr(maxd);
            auto upd = [&](char ch, int v) {
                int o = ch - 'a';
                tot -= ctr[o] > 0;
                ctr[o] += v;
                tot += ctr[o] > 0;
            };
            for(int j = 0; j < i; ++j)
                upd(s[j], 1);
            typedef unsigned long long ULL;
            unordered_map<ULL, int> vis;
            for(int j = i; j <= len; ++j) {
                if(tot <= maxLetters) {
                    ULL val = h0.get(j - i, j - 1);
                    val = val << 32 | h1.get(j - i, j - 1);
                    ++vis[val];
                }
                if(j < len) {
                    upd(s[j - i], -1);
                    upd(s[j], 1);
                }
            }
            for(auto &it : vis)
                ret = max(ret, it.second);
        }
        return ret;
    }
};
