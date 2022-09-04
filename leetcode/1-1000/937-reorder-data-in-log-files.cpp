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
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<pair<pair<int, bool>, pair<vector<string_view>, string_view> > > seq;
        for(auto &log: logs) {
            seq.push_back({{(int)seq.size(), 0}, {split(log, ' '), log}});
            seq.back().second.second = seq.back().second.first.front();
            seq.back().second.first.erase(seq.back().second.first.begin());
            auto &las = seq.back().second.first.back();
            bool &digit = seq.back().first.second = 1;
            for(char ch: las)
                if(!isdigit(ch)) {
                    digit = 0;
                    break;
                }
        }
        sort(seq.begin(), seq.end(), [&](auto const &u, auto const &v) {
            if(u.first.second != v.first.second)
                return u.first.second < v.first.second;
            if(u.first.second)
                return u.first.first < v.first.first;
            return u.second < v.second;
        });
        vector<string> ret;
        for(auto &it: seq) {
            ret.push_back(move(logs[it.first.first]));
        }
        return ret;
    }
};
