class Solution {
public:
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int> > e(n);
        for(int i = 1; i < n; ++i) {
            int p = parent[i];
            if(s[i] == s[p])
                continue;
            e[i].push_back(p);
            e[p].push_back(i);
        }
        int ans = 0, st = 0;
        vector<int> tim(n);
        for(int i = 0; i < n; ++i) {
            if(tim[i])
                continue;
            pair<int, int> cur;
            queue<pair<int, int> > que;
            tim[i] = ++st;
            que.push({i, 1});
            while(!que.empty()) {
                cur = que.front();
                que.pop();
                for(int v: e[cur.first])
                    if(tim[v] != st) {
                        tim[v] = st;
                        que.push({v, cur.second + 1});
                    }
            }
            tim[cur.first] = ++st;
            que.push({cur.first, 1});
            while(!que.empty()) {
                cur = que.front();
                que.pop();
                for(int v: e[cur.first])
                    if(tim[v] != st) {
                        tim[v] = st;
                        que.push({v, cur.second + 1});
                    }
            }
            ans = max(ans, cur.second);
        }
        return ans;
    }
};
