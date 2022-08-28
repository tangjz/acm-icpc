class Solution {
public:
    vector<int> shortestToChar(string s, char c) {
        int n = s.size(), las = -1, nxt = 0;
        vector<int> ret(n);
        for(int i = 0; i < n; ++i) {
            if(s[i] == c)
                las = i;
            for( ; nxt < n && (nxt <= i || s[nxt] != c); ++nxt);
            ret[i] = INT_MAX;
            if(las != -1)
                ret[i] = min(ret[i], i - las);
            if(nxt != n)
                ret[i] = min(ret[i], nxt - i);
        }
        return ret;
    }
};
