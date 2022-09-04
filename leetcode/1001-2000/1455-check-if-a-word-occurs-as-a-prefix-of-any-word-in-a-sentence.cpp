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
    int isPrefixOfWord(string sentence, string searchWord) {
        vector<string_view> seq = split(sentence, ' ');
        int n = seq.size(), m = searchWord.size();
        for(int i = 0; i < n; ++i)
            if(seq[i].size() >= m && seq[i].substr(0, m) == searchWord)
                return i + 1;
        return -1;
    }
};
