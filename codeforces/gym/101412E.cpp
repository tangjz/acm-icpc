#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 50, maxd = 4, dx[maxd] = {1, 0, 0, -1}, dy[maxd] = {0, 1, -1, 0};
const int dxx[maxd << 1] = {2, 2, 0, 1, 0, 1, -1, -1}, dyy[maxd << 1] = {0, 1, 2, 2, -1, -1, 0, 1};
const int max1 = maxn * maxn, max2 = maxn * maxn * maxd, INF = 0x3f3f3f3f;
typedef std::pair<int, int> Edge;
// single move
int n, m, px, py, tot, pos[maxd << 1], que[maxd << 1][max1], L, R, dis[maxd << 1][max1];
char str[maxn][maxn + 1];
// short path
int dist[max2];
std::vector<Edge> e[max2];
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > Q;
bool vis[max2];
inline int idx_1(int x, int y)
{
	return x * m + y;
}
inline void rdx_1(int o, int &x, int &y)
{
	y = o % m;
	o /= m;
	x = o;
}
inline int idx_2(int x, int y, int d)
{
	return (x * m + y) * maxd + d;
}
inline void rdx_2(int o, int &x, int &y, int &d)
{
	d = o % maxd;
	o /= maxd;
	y = o % m;
	o /= m;
	x = o;
}
inline bool valid(int x, int y)
{
	return x >= 0 && x < n && y >= 0 && y < m && str[x][y] != '*';
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		// location
		px = py = -1;
		tot = 0;
		for(int i = 0; i < n; ++i)
		{
			scanf("%s", str[i]);
			for(int j = 0; j < m; ++j)
			{
				if(str[i][j] == '.')
					pos[tot++] = idx_1(i, j);
				if(str[i][j] == 'X')
				{
					if(px == -1)
					{
						px = i;
						py = j;
					}
					str[i][j] = '*';
				}
			}
		}
		if(!px && !py)
		{
			puts("0");
			continue;
		}
		// start to near (2 time bfs)
		// assert(tot == 2);
		for(int i = 0; i < tot; ++i)
		{
			memset(dis[i], 0x3f, n * m * sizeof(int));
			L = R = 0;
			dis[i][pos[i]] = 0;
			que[i][R++] = pos[i];
			while(L < R)
			{
				int ldx = que[i][L++], lx, ly;
				rdx_1(ldx, lx, ly);
				for(int d = 0; d < maxd; ++d)
				{
					int rx = lx + dx[d], ry = ly + dy[d];
					if(valid(rx, ry))
					{
						int rdx = idx_1(rx, ry);
						if(dis[i][rdx] == INF)
						{
							dis[i][rdx] = dis[i][ldx] + 1;
							que[i][R++] = rdx;
						}
					}
				}
			}
		}
		while(!Q.empty())
			Q.pop();
		memset(dist, 0x3f, n * m * maxd * sizeof(int));
		for(int d = 0; d < maxd; ++d)
		{
			int x1 = px + dxx[d << 1], y1 = py + dyy[d << 1], x2 = px + dxx[d << 1 | 1], y2 = py + dyy[d << 1 | 1];
			if(valid(x1, y1) && valid(x2, y2))
			{
				int idx1 = idx_1(x1, y1), idx2 = idx_1(x2, y2), idx_d = idx_2(px, py, d);
				dist[idx_d] = std::min(dis[0][idx1] + dis[1][idx2], dis[0][idx2] + dis[1][idx1]);
				if(dist[idx_d] < INF)
				{
					//printf("start to (%d, %d, %d) : %d\n", px, py, d, dist[idx_d]);
					Q.push(std::make_pair(dist[idx_d], idx_d));
				}
				else
					dist[idx_d] = INF;
			}
		}
		// near to near (n * m * 8 time bfs)
		for(int i = 0; i < 2; ++i)
			for(int j = 0; j < 2; ++j)
				str[px + i][py + j] = 'o';
		for(int qx = 0; qx < n; ++qx)
			for(int qy = 0; qy < m; ++qy)
			{
				bool flag = 1;
				for(int i = 0; i < 2 && flag; ++i)
					for(int j = 0; j < 2 && flag; ++j)
						flag &= valid(qx + i, qy + j);
				if(!flag)
					continue;
				for(int i = 0; i < 2; ++i)
					for(int j = 0; j < 2; ++j)
						str[qx + i][qy + j] = '*';
				//for(int i = 0; i < n; ++i)
				//	puts(str[i]);
				for(int d = 0; d < maxd; ++d)
				{
					int x1 = qx + dxx[d << 1], y1 = qy + dyy[d << 1], x2 = qx + dxx[d << 1 | 1], y2 = qy + dyy[d << 1 | 1];
					if(valid(x1, y1) && valid(x2, y2))
					{
						int rx = qx + dx[d], ry = qy + dy[d];
						std::vector<Edge>().swap(e[idx_2(qx, qy, d)]);
						e[idx_2(qx, qy, d)].push_back(std::make_pair(1, idx_2(rx, ry, maxd - 1 - d)));
						//printf("(%d, %d, %d) to (%d, %d, %d) : %d\n", qx, qy, d, rx, ry, maxd - 1 - d, 1);
						pos[d << 1] = idx_1(x1, y1);
						pos[d << 1 | 1] = idx_1(x2, y2);
					}
					else
						pos[d << 1] = pos[d << 1 | 1] = -1;
				}
				for(int i = 0; i < maxd << 1; ++i)
				{
					if(pos[i] == -1)
						continue;
					memset(dis[i], 0x3f, n * m * sizeof(int));
					L = R = 0;
					dis[i][pos[i]] = 0;
					que[i][R++] = pos[i];
					while(L < R)
					{
						int ldx = que[i][L++], lx, ly;
						rdx_1(ldx, lx, ly);
						for(int d = 0; d < maxd; ++d)
						{
							int rx = lx + dx[d], ry = ly + dy[d];
							if(valid(rx, ry))
							{
								int rdx = idx_1(rx, ry);
								if(dis[i][rdx] == INF)
								{
									dis[i][rdx] = dis[i][ldx] + 1;
									que[i][R++] = rdx;
								}
							}
						}
					}
				}
				for(int d1 = 0; d1 < maxd; ++d1) if(pos[d1 << 1] != -1 && pos[d1 << 1 | 1] != -1)
					for(int d2 = 0; d2 < maxd; ++d2) if(pos[d2 << 1] != -1 && pos[d2 << 1 | 1] != -1)
						if(d1 != d2)
						{
							int dis1 = dis[d1 << 1][pos[d2 << 1]] + dis[d1 << 1 | 1][pos[d2 << 1 | 1]];
							int dis2 = dis[d1 << 1][pos[d2 << 1 | 1]] + dis[d1 << 1 | 1][pos[d2 << 1]];
							int cost = std::min(dis1, dis2);
							if(cost < INF)
							{
								e[idx_2(qx, qy, d1)].push_back(std::make_pair(cost, idx_2(qx, qy, d2)));
								//printf("(%d, %d, %d) to (%d, %d, %d) : %d\n", qx, qy, d1, qx, qy, d2, cost);
							}
						}
				for(int i = 0; i < 2; ++i)
					for(int j = 0; j < 2; ++j)
						str[qx + i][qy + j] = 'o';
			}
		// push to end (1 time dijkstra)
		memset(vis, 0, n * m * maxd * sizeof(bool));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			for(std::vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> second, w = it -> first;
				if(dist[v] > dist[u] + w)
				{
					dist[v] = dist[u] + w;
					Q.push(std::make_pair(dist[v], v));
				}
			}
		}
		int ans = INF;
		for(int d = 0; d < maxd; ++d)
		{
			int idx_d = idx_2(0, 0, d);
			if(ans > dist[idx_d])
				ans = dist[idx_d];
		}
		printf("%d\n", ans == INF ? -1 : ans);
	}
	return 0;
}
