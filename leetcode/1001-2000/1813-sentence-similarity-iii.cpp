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
    bool areSentencesSimilar(string sentence1, string sentence2) {
        vector<string_view> s = split(sentence1, ' '), t = split(sentence2, ' ');
        int n = s.size(), m = t.size();
        if(n > m) {
            swap(n, m);
            s.swap(t);
        }
        int L = 0, R = 0;
        for( ; L + R < n && s[L] == t[L]; ++L);
        for( ; L + R < n && s[n - 1 - R] == t[m - 1 - R]; ++R);
        return L + R == n;
    }
};
