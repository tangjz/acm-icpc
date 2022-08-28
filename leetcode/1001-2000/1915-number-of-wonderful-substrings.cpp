class Solution {
public:
    long long wonderfulSubstrings(string word) {
        typedef long long LL;
        const int maxc = 10, maxs = 1 << maxc | 1;
        LL ans = 0;
        int msk = 0;
        vector<int> ctr(maxs);
        for(char ch: word) {
            ++ctr[msk];
            msk ^= 1 << (ch - 'a');
            ans += ctr[msk];
            for(int i = 0; i < maxc; ++i)
                ans += ctr[msk ^ (1 << i)];
        }
        return ans;
    }
};
