class Solution {
public:
    int maximumInvitations(vector<int>& p) {
        int n = p.size(), m = 0;
        vector<int> vis(n, -1), cir(n, -1), rt(n, -1);
        vector<vector<int> > e(n), que;
        for(int i = 0, tim = 0; i < n; ++i) {
            if(vis[i] != -1)
                continue;
            int j, k;
            ++tim;
            for(j = i; vis[j] == -1; j = p[j])
                vis[j] = tim;
            if(vis[p[j]] == tim) {
                // new circle
                que.push_back({});
                que.back().push_back(j);
                cir[j] = m++;
                rt[j] = j;
                for(k = p[j]; k != j; k = p[k]) {
                    que.back().push_back(k);
                    cir[k] = cir[j];
                    rt[k] = k;
                }
            }
            for(k = i; k != j; k = p[k]) {
                e[p[k]].push_back(k);
                rt[k] = rt[j];
            }
        }
        int ans0 = 0, ans1 = 0;
        vector<int> dis(n, -1);
        for(auto &it: que) {
            int sz = it.size();
            ans1 = max(ans1, sz);
            if(sz > 2)
                continue;
            ans0 += sz;
            for(int s: it) {
                vector<int> seq;
                dis[s] = 0;
                seq.push_back(s);
                for(int i = 0; i < (int)seq.size(); ++i) {
                    int u = seq[i];
                    for(int v: e[u]) {
                        dis[v] = dis[u] + 1;
                        seq.push_back(v);
                    }
                }
                ans0 += dis[seq.back()];
            }
        }
        return max(ans0, ans1);
    }
};
