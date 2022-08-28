class Solution {
public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        int n = words.size();
        vector<string> res(n);
        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int const &u, int const &v) {
            return words[u].size() > words[v].size();
        });
        auto lcp = [&](string const &u, string const &v) {
            int upp = min(u.size(), v.size()), ret = 0;
            for( ; ret < upp && u[ret] == v[ret]; ++ret);
            return ret;
        };
        for(int i = 0, j; i < n; i = j) {
            for(j = i; j < n && words[ord[i]].size() == words[ord[j]].size(); ++j);
            for(int p = i; p < j; ++p) {
                int u = ord[p], com = 0;
                for(int q = i; q < j; ++q)
                    if(p != q && words[u].back() == words[ord[q]].back())
                        com = max(com, lcp(words[u], words[ord[q]]));
                int rem = words[u].size() - com - 2;
                string num = to_string(rem);
                if(rem <= 0 || com + 2 + num.size() >= words[u].size()) {
                    res[u] = words[u];
                } else {
                    res[u] = words[u].substr(0, com + 1) + num;
                    res[u].push_back(words[u].back());
                }
            }
        }
        return res;
    }
};
