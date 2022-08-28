class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int n = (int)s1.size(), cnt[2] = {};
        for(int i = 0; i < n; ++i)
            if(s1[i] != s2[i])
                ++cnt[s1[i] == 'x'];
        return (cnt[0] - cnt[1]) & 1 ? -1 : (cnt[0] + cnt[1]) / 2 + (cnt[0] & 1);
    }
};
