class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        auto minRep = [&](string &buf) {
            static const int maxd = 26;
            static int st = 0, tim[maxd] = {}, idx[maxd];
            if(!(++st)) {
                memset(tim, 0, sizeof(tim));
                ++st;
            }
            int tot = 0;
            string ret;
            for(char ch: buf) {
                int o = ch - 'a';
                if(tim[o] != st) {
                    tim[o] = st;
                    idx[o] = tot++;
                }
                ret.push_back('a' + idx[o]);
            }
            return ret;
        };
        string rep = minRep(pattern);
        vector<string> ret;
        for(auto &buf: words)
            if(minRep(buf) == rep)
                ret.push_back(buf);
        return ret;
    }
};
