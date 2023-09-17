class Solution {
public:
    long long countPalindromePaths(vector<int>& par, string s) {
        typedef long long LL;
        static const int maxn = (int)1e5 + 1;
        int n = par.size();
        static int ord[maxn], msk[maxn];
        unordered_map<int, int> sp;
        vector<vector<int> > e(n);
        for(int i = 1; i < n; ++i)
            e[par[i]].push_back(i);
        ord[0] = 0;
        msk[0] = 0;
        for(int i = 0, sz = 1; i < n; ++i) {
            int u = ord[i];
            for(int v: e[u]) {
                msk[v] = msk[u] ^ (1 << (s[v] - 'a'));
                ord[sz++] = v;
            }
            ++sp[msk[u]];
        }
        LL ans = 0;
        for(auto &it: sp) {
            ans += it.second * (it.second - 1LL) / 2;
            for(int rem = it.first, lbt; rem; rem ^= lbt) {
                lbt = rem & -rem;
                auto jt = sp.find(it.first ^ lbt);
                if(jt != sp.end())
                    ans += (LL)it.second * (jt -> second);
            }
        }
        return ans;
    }
};
