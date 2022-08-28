class Solution {
public:
    string removeOccurrences(string s, string part) {
        int n = s.size(), m = part.size();
        vector<int> nxt(m + 1);
        for(int i = 1, j = 0; i < m; ++i) {
            for( ; j && part[i] != part[j]; j = nxt[j]);
            nxt[i + 1] = part[i] == part[j] ? (++j) : 0;
        }
        vector<int> pos;
        vector<char> ch;
        for(int i = 0, j = 0; i < n; ++i) {
            for( ; j && s[i] != part[j]; j = nxt[j]);
            s[i] == part[j] && (++j);
            pos.push_back(j);
            ch.push_back(s[i]);
            if(j == m) {
                for(int k = 0; k < m; ++k) {
                    pos.pop_back();
                    ch.pop_back();
                }
                j = pos.empty() ? 0 : pos.back();
            }
        }
        string t = "";
        for(char c: ch)
            t += c;
        return t;
    }
};
