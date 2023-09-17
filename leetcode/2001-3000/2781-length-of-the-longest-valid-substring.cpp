class Solution {
public:
    int longestValidSubstring(string word, vector<string>& forbidden) {
        typedef long long LL;
        static const int maxm = 11, mod = (int)1e9 + 7, sd = 29;
        static int pw[maxm] = {1};
        int n = word.size(), ans = 0;
        vector<int> pL(n, -1), hh(n + 1);
        for(int i = 1; i <= n; ++i)
            hh[i] = ((LL)hh[i - 1] * sd + (word[i - 1] - 'a')) % mod;
        for(int i = 1; i < maxm; ++i) {
            pw[i] = (LL)pw[i - 1] * sd % mod;
            static unordered_set<int> sp;
            sp.clear();
            for(auto &it: forbidden) {
                if(it.size() != i)
                    continue;
                int hs = 0;
                for(char ch: it)
                    hs = ((LL)hs * sd + (ch - 'a')) % mod;
                sp.insert(hs);
            }
            for(int j = i; j <= n; ++j) {
                if(pL[j - 1] != -1)
                    continue;
                int hs = (hh[j] - (LL)hh[j - i] * pw[i]) % mod;
                hs < 0 && (hs += mod);
                if(sp.count(hs))
                    pL[j - 1] = j - i;
            }
        }
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j < n && i > pL[j]; ++j);
            ans = max(ans, j - i);
        }
        return ans;
    }
};
