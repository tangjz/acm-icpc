class Solution {
    void bfs(int sta, vector<vector<int> > &e, vector<int> &dis, vector<int> &pre, vector<int> &cyc) {
        int n = e.size();
        queue<int> que;
        dis[sta] = 0;
        pre[sta] = -1;
        que.push(sta);
        cyc.clear();
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            for(int v: e[u])
                if(dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    pre[v] = u;
                    que.push(v);
                } else if(cyc.empty() && v != pre[u]) {
                    int p = u, q = v;
                    vector<int> lft, rht;
                    while(p != q)
                        if(dis[p] > dis[q]) {
                            lft.push_back(p);
                            p = pre[p];
                        } else {
                            rht.push_back(q);
                            q = pre[q];
                        }
                    cyc.insert(cyc.end(), lft.begin(), lft.end());
                    cyc.push_back(p);
                    reverse(rht.begin(), rht.end());
                    cyc.insert(cyc.end(), rht.begin(), rht.end());
                }
        }
    }
public:
    int chaseGame(vector<vector<int>>& edges, int startA, int startB) {
        int n = edges.size();
        vector<int> disA(n, -1), disB(n, -1), pre(n), cyc;
        vector<vector<int> > e(n);
        for(auto &it: edges) {
            --it[0];
            --it[1];
            e[it[0]].push_back(it[1]);
            e[it[1]].push_back(it[0]);
        }
        bfs(--startA, e, disA, pre, cyc);
        bfs(--startB, e, disB, pre, cyc);
        int best = -1;
        for(int i = 0; i < n; ++i)
            if(disA[i] - disB[i] > 1)
                best = max(best, disA[i]);
        if(best == -1)
            return 1;
        bool skp = 0;
        if(cyc.size() > 3)
            for(int u: cyc)
                if(u == startB || disA[u] - disB[u] > 1) {
                    skp = 1;
                    break;
                }
        return skp ? -1 : best;
    }
};
