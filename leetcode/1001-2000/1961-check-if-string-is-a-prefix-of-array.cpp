class Solution {
public:
    bool isPrefixString(string_view s, vector<string>& words) {
        int n = s.size(), len = 0;
        for(auto &word: words) {
            int adt = word.size();
            if(len + adt > n)
                return 0;
            if(s.substr(len, adt) != word)
                return 0;
            if((len += adt) == n)
                return 1;
        }
        return 0;
    }
};
