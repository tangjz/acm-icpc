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
    vector<string> invalidTransactions(vector<string>& seq) {
        int n = seq.size();
        vector<bool> bad(n);
        vector<int> tim(n);
        vector<vector<string_view> > events;
        for(int i = 0; i < n; ++i) {
            events.push_back(split(seq[i], ','));
            tim[i] = stoi((string)events[i][2]);
            if(tim[i] >= 1000)
                bad[i] = 1;
            tim[i] = stoi((string)events[i][1]);
        }
        for(int i = 0; i < n; ++i)
            for(int j = i + 1; j < n; ++j) {
                if(bad[i] && bad[j])
                    continue;
                if(events[i][0] == events[j][0] && events[i][3] != events[j][3] && abs(tim[i] - tim[j]) <= 60)
                    bad[i] = bad[j] = 1;
            }
        vector<string> ret;
        for(int i = 0; i < n; ++i)
            if(bad[i])
                ret.push_back(move(seq[i]));
        return ret;
    }
};
