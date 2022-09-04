class Solution {
    vector<string_view> split(string_view s, char sep = ' ') {
        int n = s.size();
        vector<string_view> ret;
        for(int i = 0, j; i < n; ++i) {
            for(j = i; i < n && s[i] != sep; ++i);
            ret.push_back(s.substr(j, i - j));
        }
        return move(ret);
    }
public:
    bool wordPattern(string pattern, string s) {
        vector<string_view> words = split(s);
        int n = words.size();
        if(pattern.size() != n)
            return 0;
        map<char, string_view> ch_to_word;
        map<string_view, char> word_to_ch;
        for(int i = 0; i < n; ++i) {
            char ch = pattern[i];
            string_view word = words[i];
            if(ch_to_word.insert({ch, word}).first -> second != word)
                return 0;
            if(word_to_ch.insert({word, ch}).first -> second != ch)
                return 0;
        }
        return 1;
    }
};
