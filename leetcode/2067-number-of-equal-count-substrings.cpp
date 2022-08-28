class Solution {
public:
    int equalCountSubstrings(string s, int m) {
        const int maxd = 26;
        int n = s.size(), ans = 0;
        for(int i = 1, len; i <= maxd && (len = i * m) <= n; ++i) {
            int tot = 0;
            vector<int> ctr(maxd);
            for(int j = 0, k = 0, o; j < n; ++j) {
                o = s[j] - 'a';
                tot += !(ctr[o]++);
                for( ; k < j && !(tot <= i && ctr[o] <= m); ++k) {
                    int o2 = s[k] - 'a';
                    tot -= !(--ctr[o2]);
                }
                if(j - k + 1 == len)
                    ++ans;
            }
        }
        return ans;
    }
};
