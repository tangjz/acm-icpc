class Solution {
public:
    vector<int> metroRouteDesignI(vector<vector<int>>& lines, int start, int end) {
        int n = lines.size();
        vector<int> lineDis(n, INT_MAX);
        map<int, vector<pair<int, int> > > pos;
        map<int, int> dis;
        map<int, vector<int> > sol;
        for(int i = 0; i < n; ++i) {
            int m = lines[i].size();
            for(int j = 0; j < m; ++j) {
                pos[lines[i][j]].push_back({i, j});
                dis[lines[i][j]] = INT_MAX;
            }
        }
        queue<int> lineQue, que;
        dis[end] = 0;
        sol[end] = {end};
        for(auto &it: pos[end]) {
            lineDis[it.first] = 0;
            lineQue.push(it.first);
        }
        while(!lineQue.empty()) {
            int x = lineQue.front();
            lineQue.pop();
            if(lineDis[x] > dis[start])
                break;
            int m = lines[x].size(), low = INT_MAX;
            for(int y: lines[x])
                low = min(low, dis[y]);
            // printf("line %d (%d): lineDis %d dis %d\n", x, m, lineDis[x], low);
            assert(low == lineDis[x]);
            auto cmp = [&](vector<int>::iterator head, vector<int>::iterator tail, vector<int> &lft, vector<int> &rht) -> bool {
                unordered_set<int> vis;
                int len = tail - head;
                for(int i = 0; i < len; ++i)
                    if(!vis.insert(*(head + i)).second)
                        return 0;
                for(int x: lft)
                    if(!vis.insert(x).second)
                        return 0;
                for(int i = 0; i < len; ++i) {
                    if(i >= rht.size())
                        return 0;
                    if(*(head + i) != rht[i])
                        return *(head + i) < rht[i];
                }
                for(int i = 0; i < (int)rht.size(); ++i) {
                    if(len + i >= rht.size())
                        return 0;
                    if(lft[i] != rht[len + i])
                        return lft[i] < rht[len + i];
                }
                return len + lft.size() < rht.size();
            };
            for(int t = 0; t < 2; ++t) {
                int las = -1;
                vector<int> best;
                for(int i = 0; i <= m; ++i) {
                    if(i < m && dis[lines[x][i]] != low)
                        continue;
                    // printf("found %d (%d)\n", i < m ? lines[x][i] : -1, i);
                    if(las == -1) {
                        best = sol[lines[x][i]];
                        las = i;
                        continue;
                    }
                    vector<int> lft;
                    for(int j = i - (i == m); j > las; --j)
                        lft.push_back(lines[x][j]);
                    for(int j = las + 1; j < i; ++j) {
                        int z = lines[x][j];
                        for(auto &it: pos[z])
                            if(lineDis[it.first] > low + 1) {
                                lineDis[it.first] = low + 1;
                                lineQue.push(it.first);
                            }
                        if(dis[z] < low + 1)
                            continue;
                        vector<int>::iterator tail = lft.end(), head = tail - (j - las);
                        if(dis[z] > low + 1 || (dis[z] == low + 1 && cmp(head, tail, best, sol[z]))) {
                            dis[z] = low + 1;
                            sol[z].clear();
                            sol[z].insert(sol[z].end(), head, tail);
                            sol[z].insert(sol[z].end(), best.begin(), best.end());
                            // printf("new sol %d (%d):", z, dis[z]);
                            // for(int x: sol[z])
                            //     printf(" %d", x);
                            // puts("");
                        }
                    }
                    if(i == m)
                        continue;
                    lft.insert(lft.end(), best.begin(), best.end());
                    if(cmp(lft.begin(), lft.begin(), lft, sol[lines[x][i]])) {
                        best = lft;
                    } else {
                        best = sol[lines[x][i]];
                    }
                    las = i;
                }
                reverse(lines[x].begin(), lines[x].end());
            }
        }
        return sol[start];
    }
};
