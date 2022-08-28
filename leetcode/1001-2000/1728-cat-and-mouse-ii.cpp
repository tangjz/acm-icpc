class Solution {
    int n;
    int getID(int u, int v, int turn) {
        return (u * n + v) << 1 | (turn - 1);
    }
    void setID(int id, int &u, int &v, int &turn) {
        turn = (id & 1) + 1;
        v = (id >> 1) % n;
        u = (id >> 1) / n;
    }
public:
    bool canMouseWin(vector<string>& g, int cD, int mD) {
        int r = (int)g.size();
        int c = (int)g[0].size();
        n = r * c;
        vector<int> ban(n);
        vector<vector<int> > cE(n, vector<int>()), cRE(n, vector<int>());
        vector<vector<int> > mE(n, vector<int>()), mRE(n, vector<int>());
        int cS, mS, T;
        for(int i = 0; i < n; ++i) {
            int iX = i / c, iY = i % c;
            if(g[iX][iY] == '#') {
                ban[i] = 1;
                continue;
            }
            if(g[iX][iY] == 'C') {
                cS = i;
                g[iX][iY] = '.';
            } else if(g[iX][iY] == 'M') {
                mS = i;
                g[iX][iY] = '.';
            } else if(g[iX][iY] == 'F') {
                T = i;
                continue;
            }
            const int dt[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for(int o = 0; o < 4; ++o) {
                int jX = iX - dt[o][0], jY = iY - dt[o][1];
                for(int dis = 0; dis <= cD || dis <= mD; ++dis) {
                    jX += dt[o][0];
                    jY += dt[o][1];
                    if(jX < 0 || jX >= r || jY < 0 || jY >= c || g[jX][jY] == '#')
                        break;
                    int j = jX * c + jY;
                    if(dis <= cD) {
                        cE[i].push_back(j);
                        cRE[j].push_back(i);
                    }
                    if(dis <= mD) {
                        mE[i].push_back(j);
                        mRE[j].push_back(i);
                    }
                }
            }
        }
        int m = n * n * 2;
        vector<pair<int, int> > state(m);
        queue<int> que;
        for(int i = 0; i < m; ++i) {
            int u, v, turn;
            setID(i, u, v, turn);
            if(ban[u] || ban[v])
                continue;
            auto &it = state[i];
            if(u == T && u != v) {
                it.first = 1;
            } else if(v == T || u == v) {
                it.first = 2;
            } else {
                it.first = 0;
            }
            if(it.first != 0) {
                que.push(i);
            } else {
                if(turn == 1) {
                    it.second = (int)mE[u].size();
                } else {
                    it.second = (int)cE[v].size();
                }
            }
        }
        int sta = getID(mS, cS, 1);
        while(!state[sta].first && !que.empty()) {
            int i = que.front(), u, v, turn;
            que.pop();
            setID(i, u, v, turn);
            auto &it = state[i];
            if(turn == 2) {
                for(int p : mRE[u]) {
                    int j = getID(p, v, 1);
                    auto &jt = state[j];
                    if(jt.first != 0)
                        continue;
                    if(it.first == 1) {
                        jt.first = 1;
                    } else if(!(--jt.second)) {
                        jt.first = 2;
                    }
                    if(jt.first != 0) {
                        que.push(j);
                    }
                }
            } else {
                for(int p : cRE[v]) {
                    int j = getID(u, p, 2);
                    auto &jt = state[j];
                    if(jt.first != 0)
                        continue;
                    if(it.first == 2) {
                        jt.first = 2;
                    } else if(!(--jt.second)) {
                        jt.first = 1;
                    }
                    if(jt.first != 0) {
                        que.push(j);
                    }
                }
            }
        }
        return state[sta].first == 1;
    }
};
