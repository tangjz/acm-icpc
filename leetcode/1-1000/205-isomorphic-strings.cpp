class Solution {
public:
    bool isIsomorphic(string s, string t) {
        if(s.size() != t.size())
            return false;
        const int maxd = 256;
        vector<vector<int> > sc(maxd), tc(maxd);
        int pos = 0;
        for(char ch: s)
            sc[ch].push_back(pos++);
        pos = 0;
        for(char ch: t)
            tc[ch].push_back(pos++);
        sort(sc.begin(), sc.end());
        sort(tc.begin(), tc.end());
        return sc == tc;
    }
};
