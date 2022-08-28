class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int n = (int)s1.size(), ctr = 0;
        for(int i = 0; i < n; ++i)
            ctr += s1[i] != s2[i];
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        return ctr <= 2 && s1 == s2;
    }
};
