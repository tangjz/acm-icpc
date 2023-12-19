class Solution {
public:
    long long beautifulSubstrings(string s, int m) {
        typedef long long LL;
        unordered_set<char> vowel = {'a', 'e', 'i', 'o', 'u'};
        int n = s.size();
        vector<int> psum = {0}, cand;
        for(int i = 0; i < m; ++i)
            if(i * i % m == 0)
                cand.push_back(i);
        vector<vector<int> > pos(n + n + 1);
        pos[n].push_back(0);
        for(int i = 1; i <= n; ++i) {
            psum.push_back(psum.back() + (vowel.find(s[i - 1]) != vowel.end()));
            pos[n + psum.back() + psum.back() - i].push_back(i);
        }
        static const int maxm = 1001;
        static int st = 0, ctr[maxm], tim[maxm] = {};
        LL ans = 0;
        for(auto &vec: pos) {
            if(vec.empty())
                continue;
            if(!(++st)) {
                memset(tim, 0, sizeof tim);
                ++st;
            }
            for(int i: vec) {
                int u = psum[i] % m, v;
                for(int dt: cand) {
                    (v = u - dt) < 0 && (v += m);
                    tim[v] == st && (ans += ctr[v]);
                }
                ctr[u] = tim[u] != st ? 1 : (ctr[u] + 1);
                tim[u] = st;
            }
        }
        return ans;
    }
};
