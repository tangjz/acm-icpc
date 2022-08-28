class Solution {
public:
    int countDistinct(string s) {
        int n = s.size();
        auto lcp = [&](int u, int v) {
            int upp = n - max(u, v);
            for(int i = 0; i < upp; ++i)
                if(s[u + i] != s[v + i])
                    return i;
            return upp;
        };
        auto cmp = [&](int const &u, int const &v) {
            int com = lcp(u, v);
            if(max(u, v) + com == n)
                return u > v;
            return s[u + com] < s[v + com];
        };
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), cmp);
        int ans = 0, las = -1;
        for(int i: ord) {
            int com = las == -1 ? 0 : lcp(las, i);
            ans += n - i - com;
            las = i;
        }
        return ans;
    }
};
