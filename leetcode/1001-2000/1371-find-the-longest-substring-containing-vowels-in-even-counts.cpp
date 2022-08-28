class Solution {
public:
    int findTheLongestSubstring(string s) {
        const char *pat = "aeiou";
        const int maxn = 5, maxd = 1 << maxn | 1, INF = (int)1e6;
        vector<int> fir(maxd, INF);
        int pos = 0, msk = 0, ans = 0;
        fir[msk] = -1;
        for(char ch : s) {
            for(int i = 0; i < maxn; ++i)
                if(ch == pat[i])
                    msk ^= 1 << i;
            fir[msk] = min(fir[msk], pos);
            ans = max(ans, pos - fir[msk]);
            ++pos;
        }
        return ans;
    }
};
