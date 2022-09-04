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
    vector<string> sortFeatures(vector<string>& features, vector<string>& responses) {
        unordered_map<string, pair<int, int> > rnk;
        for(auto &it: features)
            rnk.insert({it, {0, rnk.size()}});
        unordered_set<string> vis;
        for(auto &rsp: responses) {
            vis.clear();
            for(auto &word_view: split(rsp, ' ')) {
                string word = (string)word_view;
                auto it = rnk.find(word);
                if(it == rnk.end() || vis.count(word))
                    continue;
                --(it -> second).first;
                vis.insert(word);
            }
        }
        sort(features.begin(), features.end(), [&](string const &u, string const &v) {
            return rnk[u] < rnk[v];
        });
        return features;
    }
};
