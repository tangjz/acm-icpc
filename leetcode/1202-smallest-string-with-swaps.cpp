class Solution {
public:
    string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
        int n = s.size();
        vector<vector<int> > e(n);
        for(auto &it: pairs) {
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        vector<bool> vis(n);
        for(int i = 0; i < n; ++i) {
            if(vis[i])
                continue;
            string t = "";
            vector<int> que;
            vis[i] = 1;
            t.push_back(s[i]);
            que.push_back(i);
            for(int j = 0; j < (int)que.size(); ++j) {
                int u = que[j];
                for(int v: e[u]) {
                    if(vis[v])
                        continue;
                    vis[v] = 1;
                    t.push_back(s[v]);
                    que.push_back(v);
                }
            }
            sort(t.begin(), t.end());
            sort(que.begin(), que.end());
            for(int j = 0; j < (int)que.size(); ++j)
                s[que[j]] = t[j];
        }
        return s;
    }
};
