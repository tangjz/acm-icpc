class Solution {
public:
    int minSteps(string s, string t) {
        const int maxd = 26;
        vector<int> a(maxd);
        for(char ch: s)
            ++a[(int)(ch - 'a')];
        for(char ch: t)
            --a[(int)(ch - 'a')];
        int ans = 0;
        for(int i = 0; i < maxd; ++i)
            ans += abs(a[i]);
        return ans;
    }
};
