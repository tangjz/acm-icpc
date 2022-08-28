class Solution {
public:
    vector<string> expand(string s) {
        int n = s.size();
        string buf = "";
        vector<string> ret = {""};
        for(int i = 0; i < n; ++i) {
            if(s[i] != '{') {
                buf.push_back(s[i]);
                continue;
            }
            string cand = "";
            for( ; s[i] != '}'; i += 2)
                cand.push_back(s[i + 1]);
            sort(cand.begin(), cand.end());
            vector<string> nxt;
            nxt.reserve(ret.size() * cand.size());
            for(auto &it: ret)
                for(char ch: cand) {
                    string tmp = it + buf;
                    tmp.push_back(ch);
                    nxt.push_back(move(tmp));
                }
            buf = "";
            ret = move(nxt);
        }
        for(auto &it: ret)
            it += buf;
        return ret;
    }
};
