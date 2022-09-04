class Solution {
    vector<string_view> split(string_view s, char sep = '.', bool skipEmpty = 0) {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0; i < n; ++i) {
            int j = i;
            for( ; i < n && s[i] != sep; ++i);
            if(!skipEmpty || j < i)
                ret.push_back(s.substr(j, i - j));
        }
        if(!skipEmpty && !s.empty() && s.back() == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
    string join(vector<string_view> seq, char sep = ' ') {
        int len = 0;
        for(auto &it: seq)
            len += (len > 0) + it.size();
        string ret;
        ret.reserve(len);
        for(auto &it: seq) {
            if(!ret.empty())
                ret.push_back(sep);
            ret += it;
        }
        return ret;
    }
public:
    string truncateSentence(string s, int k) {
        vector<string_view> seq = split(s, ' ');
        if(seq.size() > k)
            seq.resize(k);
        return join(seq, ' ');
    }
};
