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
public:
    string reorderSpaces(string text) {
        vector<string_view> seq = split(text, ' ', 1);
        int n = 0, cnt = text.size();
        for(auto &it: seq) {
            ++n;
            cnt -= it.size();
        }
        int mid = n > 1 ? cnt / (n - 1) : 1;
        cnt -= mid * (n - 1);
        string ret = "";
        ret.resize(text.size());
        for(int i = n - 1, j = ret.size() - 1; i >= 0; --i) {
            int tail = i + 1 < n ? mid : cnt;
            while(tail--)
                ret[j--] = ' ';
            for(int k = seq[i].size() - 1; k >= 0; --k)
                ret[j--] = seq[i][k];
        }
        return ret;
    }
};
