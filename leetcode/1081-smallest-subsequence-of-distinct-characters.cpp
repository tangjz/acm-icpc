class Solution {
public:
    string smallestSubsequence(string s) {
        const int maxd = 26;
        int n = s.size(), m = 0;
        vector<vector<int> > pos(maxd);
        for(int i = n - 1; i >= 0; --i) {
            int o = s[i] - 'a';
            m += pos[o].empty();
            pos[o].push_back(i);
        }
        string ret = "";
        vector<bool> vis(maxd);
        for(int i = 0, j = 0; i < m; ++i) {
            int best[2] = {-1, -1};
            for(int k = 0; k < maxd; ++k)
                if(!vis[k] && !pos[k].empty()) {
                    for(int x = 0, y = k; x < 2; ++x) {
                        if(best[x] == -1 || pos[best[x]].front() > pos[y].front()) {
                            swap(y, best[x]);
                        }
                    }
                }
            for(int k = 0; k < maxd; ++k)
                if(!vis[k] && !pos[k].empty()) {
                    int x = pos[k].back(), y = best[k == best[0]];
                    y = y == -1 ? n : pos[y].front();
                    if(x < y) {
                        ret.push_back('a' + k);
                        for( ; j <= x; ++j) {
                            int o = s[j] - 'a';
                            pos[o].pop_back();
                        }
                        vis[k] = 1;
                        break;
                    }
                }
        }
        return ret;
    }
};
