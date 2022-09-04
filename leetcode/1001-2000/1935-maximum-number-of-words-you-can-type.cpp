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
    int canBeTypedWords(string text, string brokenLetters) {
        unordered_set<char> bad(brokenLetters.begin(), brokenLetters.end());
        int cnt = 0;
        for(auto &word: split(text, ' ')) {
            bool ban = 0;
            for(char ch: word)
                if(bad.count(ch)) {
                    ban = 1;
                    break;
                }
            cnt += !ban;
        }
        return cnt;
    }
};
