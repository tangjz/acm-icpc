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
    string discountPrices(string sentence, int discount) {
        string ret;
        for(auto &item: split(sentence, ' ')) {
            if(item.size() < 2 || item.front() != '$' || !isdigit(item.substr(1))) {
                ret += (string)item + " ";
                continue;
            }
            long long val = stol((string)item.substr(1));
            static char buf[31];
            sprintf(buf, "$%.2f", val * (100 - discount) / 100.0);
            ret += (string)buf + " ";
        }
        ret.pop_back();
        return ret;
    }
};
