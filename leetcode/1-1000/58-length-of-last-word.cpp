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
    int lengthOfLastWord(string_view s) {
        vector<string_view> seq = split(s, ' ');
        while(!seq.empty() && seq.back().empty())
            seq.pop_back();
        return seq.empty() ? 0 : seq.back().size();
    }
};
