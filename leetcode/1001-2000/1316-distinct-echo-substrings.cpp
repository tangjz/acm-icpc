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
    int distinctEchoSubstrings(string text) {
        const int mod0 = (int)1e9 + 7, seed0 = 37;
        const int mod1 = (int)1e9 + 403, seed1 = 29;
        int len = (int)text.size();
        Hash h0(mod0, seed0), h1(mod1, seed1);
        h0.parse(text);
        h1.parse(text);
        int ret = 0;
        for(int i = 1; i + i <= len; ++i) {
            typedef unsigned long long ULL;
            unordered_set<ULL> Hash;
            for(int L = 0, M = i, R = i + i; R <= len; ++L, ++M, ++R) {
                ULL val = h0.get(L, R - 1);
                val = val << 32 | h1.get(L, R - 1);
                if(Hash.insert(val).second && h0.get(L, M - 1) == h0.get(M, R - 1) && h1.get(L, M - 1) == h1.get(M, R - 1))
                    ++ret;
            }
        }
        return ret;
    }
};
