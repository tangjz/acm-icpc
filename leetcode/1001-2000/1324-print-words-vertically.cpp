class Solution {
    vector<string_view> split(string_view s, char sep = '.') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        if(!s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    vector<string> printVertically(string s) {
        vector<string_view> seq = split(s, ' ');
        int n = 0;
        for(auto &it: seq)
            n = max(n, (int)it.size());
        vector<string> ret(n);
        for(int i = 0; i < n; ++i) {
            auto &tmp = ret[i];
            for(auto &it: seq)
                tmp.push_back(i < it.size() ? it[i] : ' ');
            while(!tmp.empty() && tmp.back() == ' ')
                tmp.pop_back();
        }
        return ret;
    }
};
