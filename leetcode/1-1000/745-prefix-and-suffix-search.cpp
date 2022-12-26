class WordFilter {
    typedef long long LL;
    map<LL, unordered_map<LL, int> > Hash;
public:
    WordFilter(vector<string>& words) {
        for(int idx = 0; idx < (int)words.size(); ++idx) {
            auto &buf = words[idx];
            int m = buf.size();
            LL cur = 0;
            vector<LL> suf(m);
            for(int i = 0; i < m; ++i) {
                cur = cur * 27 + (buf[m - 1 - i] - 'a' + 1);
                suf[i] = cur;
            }
            cur = 0;
            for(int i = 0; i < m; ++i) {
                cur = cur * 27 + (buf[i] - 'a' + 1);
                auto &vec = Hash[cur];
                for(LL x: suf) {
                    int &tmp = vec[x];
                    tmp = max(tmp, idx);
                }
            }
        }
    }

    int f(string prefix, string suffix) {
        LL cur = 0;
        for(char ch: prefix)
            cur = cur * 27 + (ch - 'a' + 1);
        auto it = Hash.find(cur);
        if(it == Hash.end())
            return -1;
        cur = 0;
        reverse(suffix.begin(), suffix.end());
        for(char ch: suffix)
            cur = cur * 27 + (ch - 'a' + 1);
        auto jt = it -> second.find(cur);
        return jt == it -> second.end() ? -1 : jt -> second;
    }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(prefix,suffix);
 */
