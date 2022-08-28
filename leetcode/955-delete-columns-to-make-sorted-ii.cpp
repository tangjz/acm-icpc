class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size(), ans = 0;
        vector<pair<int, int> > cur = {{0, n - 1}};
        for(int i = 0; i < m; ++i) {
            bool bad = 0;
            vector<pair<int, int> > nxt;
            for(auto &it: cur) {
                int L = it.first, R = it.second;
                for(int j = L + 1; j <= R; ++j) {
                    if(strs[j - 1][i] > strs[j][i]) {
                        bad = 1;
                        break;
                    }
                    if(strs[j - 1][i] < strs[j][i]) {
                        nxt.push_back({L, j - 1});
                        L = j;
                    }
                }
                if(bad)
                    break;
                nxt.push_back({L, R});
            }
            if(bad) {
                ++ans;
            } else {
                cur = move(nxt);
            }
        }
        return ans;
    }
};
