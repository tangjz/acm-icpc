class Solution {
    int count(string_view s, char pat) {
        int cnt = 0;
        for(char ch: s)
            cnt += ch == pat;
        return cnt;
    }
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
    int countValidWords(string sentence) {
        int ans = 0;
        for(auto &word: split(sentence, ' ', 1)) {
            bool bad = 0, found = 0;
            for(char ch: "!.,") {
                auto p = word.find(ch);
                if(p == string::npos)
                    continue;
                if(p != word.size() - 1) {
                    bad = 1;
                    break;
                }
                found = 1;
            }
            if(bad)
                continue;
            if(found)
                word = word.substr(0, word.size() - 1);
            int occ = count(word, '-');
            if(occ > 1 || (occ == 1 && (word.front() == '-' || word.back() == '-')))
                continue;
            for(char ch: word)
                if(isdigit(ch)) {
                    bad = 1;
                    break;
                }
            ans += !bad;
        }
        return ans;
    }
};
