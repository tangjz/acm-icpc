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
    string sortSentence(string s) {
        vector<string_view> A = split(s, ' '), B(A.size());
        for(auto &it: A) {
            int p = it.back() - '1';
            B[p] = it.substr(0, it.size() - 1);
        }
        return join(B, ' ');
    }
};
