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
    int numDifferentIntegers(string word) {
        for(char &ch: word)
            if(!isdigit(ch))
                ch = ' ';
        vector<string_view> seq = split(word, ' ', 1);
        unordered_set<string> ret;
        for(auto &it: seq) {
            int sta = 0;
            for( ; sta + 1 < it.size() && it[sta] == '0'; ++sta);
            ret.insert((string)it.substr(sta));
        }
        return ret.size();
    }
};
