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
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string_view> seq = split(text, ' ');
        vector<string> ans;
        for(int i = 0; i + 2 < (int)seq.size(); ++i)
            if(seq[i] == first && seq[i + 1] == second)
                ans.push_back((string)seq[i + 2]);
        return ans;
    }
};
