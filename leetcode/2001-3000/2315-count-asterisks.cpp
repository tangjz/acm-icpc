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
    int count(string_view s, char pat) {
        int cnt = 0;
        for(char ch: s)
            cnt += ch == pat;
        return cnt;
    }
public:
    int countAsterisks(string s) {
        int ans = 0;
        vector<string_view> seq = split(s, '|');
        for(int i = 0; i < (int)seq.size(); i += 2)
            ans += count(seq[i], '*');
        return ans;
    }
};
