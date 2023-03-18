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
    bool isCircularSentence(string sentence) {
        vector<string_view> seq = split(sentence, ' ');
        int n = seq.size();
        for(int i = 0; i < n; ++i)
            if(seq[i].back() != seq[(i + 1) % n].front())
                return 0;
        return 1;
    }
};