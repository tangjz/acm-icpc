class Solution {
public:
    vector<int> movesToStamp(string s, string t) {
        int n = s.size(), m = t.size();
        vector<int> ret, deg(m);
        vector<vector<int> > e(m);
        queue<int> que;
        for(int i = 0; i <= m - n; ++i) {
            for(int j = 0; j < n; ++j)
                if(s[j] != t[i + j]) {
                    ++deg[i];
                    e[i + j].push_back(i);
                }
            if(!deg[i])
                que.push(i);
        }
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            bool upd = 0;
            for(int j = 0; j < n; ++j)
                if(t[u + j] != '?') {
                    upd = 1;
                    t[u + j] = '?';
                    for(int v: e[u + j])
                        if(!(--deg[v]))
                            que.push(v);
                }
            if(upd)
                ret.push_back(u);
        }
        for(int i = 0; i < m; ++i)
            if(t[i] != '?')
                return {};
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
