class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), m = n * n;
        vector<pair<int, int> > pos(m + 1);
        for(int i = n - 1, x = 1; i >= 0; --i)
            if((n - i) & 1) {
                for(int j = 0; j < n; ++j)
                    pos[x++] = {i, j};
            } else {
                for(int j = n - 1; j >= 0; --j)
                    pos[x++] = {i, j};
            }
        vector<int> dis(m + 1, -1);
        queue<int> que;
        dis[1] = 0;
        que.push(1);
        while(!que.empty()) {
            int u = que.front();
            que.pop();
            int d = dis[u];
            if(u == m)
                return d;
            for(int v = u + 1; v <= m && v <= u + 6; ++v) {
                int x, y;
                tie(x, y) = pos[v];
                int w = board[x][y];
                if(w == -1)
                    w = v;
                if(dis[w] == -1) {
                    dis[w] = d + 1;
                    que.push(w);
                }
            }
        }
        return -1;
    }
};
