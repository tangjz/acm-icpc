class Solution {
public:
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) {
        vector<pair<int, int> > f(n + 1, make_pair(1, -1));
        pair<int, int> res;
        auto upd = [&](pair<int, int> &x, pair<int, int> y) {
            x.first < y.first && (x = y, 1);
        };
        for(int i = 0; i < n; ++i) {
            upd(res, make_pair(f[i].first, i));
            for(int j = i + 1; j < n; ++j) {
                if(groups[i] == groups[j] || words[i].size() != words[j].size())
                    continue;
                int d = 0;
                for(int k = words[i].size() - 1; k >= 0 && d < 2; d += words[i][k] != words[j][k], --k);
                if(d == 1)
                    upd(f[j], make_pair(f[i].first + 1, i));
            }
        }
        vector<string> ret;
        for(int i = res.second; i >= 0; ret.push_back(words[i]), i = f[i].second);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
