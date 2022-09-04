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
    vector<string> uncommonFromSentences(string_view s1, string_view s2) {
        vector<string_view> seq1 = split(s1, ' '), seq2 = split(s2, ' ');
        unordered_map<string_view, int> ctr;
        for(auto &it: seq1)
            ++ctr[it];
        for(auto &it: seq2)
            ++ctr[it];
        vector<string> ret;
        for(auto &it: ctr)
            if(it.second == 1)
                ret.push_back((string)it.first);
        return ret;
    }
};
