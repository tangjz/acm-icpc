class Solution {
    vector<string_view> split(string_view s, string_view sep = "->", bool skipEmpty = 1) {
        int n = s.size();
        vector<string_view> ret;
        if(sep.empty()) {
            for(int i = 0; i < n; ++i)
                ret.push_back(s.substr(i, 1));
            return move(ret);
        }
        for(int i = 0; i < n; i += sep.size()) {
            int j = i;
            for( ; i < n && s.substr(i, sep.size()) != sep; ++i);
            if(!skipEmpty || j < i)
                ret.push_back(s.substr(j, i - j));
        }
        if(!skipEmpty && !s.empty() && s.substr(s.size() - sep.size()) == sep)
            ret.push_back(s.substr(s.size()));
        return move(ret);
    }
public:
    int adventureCamp(vector<string>& seq) {
        int n = seq.size(), ans = -1, cnt = 0;
        unordered_set<string> vis;
        for(auto &it: split(seq[0]))
            vis.insert((string)it);
        for(int i = 1; i < n; ++i) {
            int cur = 0;
            for(auto &it: split(seq[i]))
                cur += vis.insert((string)it).second;
            if(cur > cnt) {
                cnt = cur;
                ans = i;
            }
        }
        return ans;
    }
};
