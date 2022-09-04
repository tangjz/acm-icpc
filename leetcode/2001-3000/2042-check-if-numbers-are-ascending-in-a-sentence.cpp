class Solution {
    bool isdigit(string_view s) {
        for(char ch: s)
            if(!::isdigit(ch))
                return 0;
        return !s.empty();
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
    bool areNumbersAscending(string s) {
        int las = -1;
        for(auto &part: split(s, ' '))
            if(isdigit(part)) {
                int cur = stoi((string)part);
                if(las >= cur)
                    return 0;
                las = cur;
            }
        return 1;
    }
};
