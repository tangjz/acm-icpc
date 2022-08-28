class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        const int INF = 0x3f3f3f3f;
        int r = grid.size(), c = grid[0].size(), n = r * c, m = 0, s = -1;
        for(int x = 0; x < r; ++x)
            for(int y = 0; y < c; ++y)
                if(grid[x][y] == '@') {
                    s = x * c + y;
                    grid[x][y] = '.';
                } else if(grid[x][y] >= 'a' && grid[x][y] <= 'z') {
                    m = max(m, (int)(grid[x][y] - 'a') + 1);
                }
        int all = (1 << m) - 1;
        vector<int> dis(n << m, INF);
        queue<int> que;
        dis[s << m] = 0;
        que.push(s << m);
        while(!que.empty()) {
            int u = que.front(), umsk = u & all;
            int ux = (u >> m) / c, uy = (u >> m) % c;
            que.pop();
            for(int dx = -1; dx <= 1; ++dx)
                for(int dy = -1; dy <= 1; ++dy) {
                    if(!dx == !dy)
                        continue;
                    int vx = ux + dx, vy = uy + dy, vmsk = umsk;
                    if(vx < 0 || vx >= r || vy < 0 || vy >= c || grid[vx][vy] == '#')
                        continue;
                    char ch = grid[vx][vy];
                    if(ch >= 'a' && ch <= 'z') {
                        vmsk |= 1 << (int)(ch - 'a');
                    } else if(ch >= 'A' && ch <= 'Z') {
                        if(!((vmsk >> (int)(ch - 'A')) & 1))
                            continue;
                    }
                    int v = ((u >> m) + dx * c + dy) << m | vmsk;
                    if(dis[v] < INF)
                        continue;
                    dis[v] = dis[u] + 1;
                    if(vmsk == all)
                        return dis[v];
                    que.push(v);
                }
        }
        return -1;
    }
};
