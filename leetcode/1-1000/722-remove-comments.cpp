class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        string buf = "";
        for(auto &it: source)
            buf += it + "\n";
        int n = buf.size(), tot = 0;
        for(int i = 0, j; i < n; ) {
            if(i + 1 < n && buf[i] == '/' && buf[i + 1] == '/') {
                for(j = i + 2; j < n && buf[j] != '\n'; ++j);
                i = j;
                continue;
            }
            if(i + 1 < n && buf[i] == '/' && buf[i + 1] == '*') {
                for(j = i + 2; j < n && !(j + 1 < n && buf[j] == '*' && buf[j + 1] == '/'); ++j);
                i = j + 2;
                continue;
            }
            buf[tot++] = buf[i++];
        }
        if(!(tot && buf[tot - 1] == '\n'))
            buf[tot++] = '\n';
        buf.resize(tot);
        vector<string> ret;
        for(int i = 0, j; i < tot; ++i) {
            for(j = i; i < tot && buf[i] != '\n'; ++i);
            if(i - j > 0)
                ret.push_back(buf.substr(j, i - j));
        }
        return ret;
    }
};
