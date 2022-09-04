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
    string toGoatLatin(string sentence) {
        vector<string_view> words = split(sentence, ' ');
        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};
        int n = words.size();
        string ret = "";
        for(int i = 0; i < n; ++i) {
            if(i > 0)
                ret.push_back(' ');
            char fir = words[i][0];
            if(!vowels.count(tolower(fir))) {
                ret += (string)words[i].substr(1);
                ret.push_back(fir);
            } else {
                ret += (string)words[i];
            }
            ret.push_back('m');
            for(int j = 0; j < i + 2; ++j)
                ret.push_back('a');
        }
        return ret;
    }
};
