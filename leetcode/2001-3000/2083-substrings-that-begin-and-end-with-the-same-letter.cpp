class Solution {
public:
    long long numberOfSubstrings(string s) {
        static const int maxd = 26;
        vector<int> ctr(maxd);
        for(char ch: s)
            ++ctr[(int)(ch - 'a')];
        long long ans = 0;
        for(int i = 0; i < maxd; ++i)
            ans += ctr[i] * (ctr[i] + 1LL) / 2;
        return ans;
    }
};
