class Solution {
public:
    bool canConvertString(string s, string t, int k) {
        const int maxd = 26;
        int n = (int)s.size();
        if(n != (int)t.size())
            return false;
        vector<int> ctr(maxd);
        for(int i = 0; i < n; ++i) {
            int u = s[i] - 'a';
            int v = t[i] - 'a';
            ++ctr[(v - u + maxd) % maxd];
        }
        for(int i = 1; i < maxd; ++i) {
            int need = ctr[i];
            if(!need)
                continue;
            int cost = i + (need - 1) * maxd;
            if(k < cost)
                return false;
        }
        return true;
    }
};
