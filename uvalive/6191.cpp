#include <queue>
#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
const int maxn = 3, maxd = 7, delta = 420, maxs = maxn * delta + 1, maxm = 33724, maxk = 72, mod = 960991;
typedef std::pair<double, int> Edge;
int tot, pos[mod];
struct Hash
{
	int nxt, val;
} hh[maxm];
inline void HashInsert(int val)
{
	int idx = val % mod;
	for(int it = pos[idx]; it != -1; it = hh[it].nxt)
		if(hh[it].val == val)
			return;
	hh[tot] = (Hash){pos[idx], val};
	pos[idx] = tot++;
}
inline int HashFind(int val)
{
	int idx = val % mod;
	for(int it = pos[idx]; it != -1; it = hh[it].nxt)
		if(hh[it].val == val)
			return it;
	return -1;
}
struct Point
{
	int x, y, z;
	inline bool read()
	{
		bool ret = scanf("%d%d%d", &x, &y, &z) == 3;
		x *= delta;
		y *= delta;
		z *= delta;
		return ret;
	}
	inline bool isZero()
	{
		return !x && !y && !z;
	}
	inline Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y, z - t.z};
	}
	inline int mode2() const
	{
		return x * x + y * y + z * z;
	}
	inline double mode() const
	{
		return sqrt(mode2());
	}
	inline int getID() const
	{
		return HashFind((x * maxs + y) * maxs + z);
	}
} sp, tp;
int dir_tot, dir_seq[delta << 2][2];
int sysTim, tim[maxm];
char str[maxn][maxn][maxn + 1];
double dist[maxm];
bool vis[maxm];
std::vector<Edge> e[maxm];
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge> > Q;
inline void flushEdge(int u)
{
	if(tim[u] != sysTim)
	{
		tim[u] = sysTim;
		std::vector<Edge>().swap(e[u]);
	}
}
inline void addEdge(int u, int v, double w)
{
	flushEdge(u);
	e[u].push_back(std::make_pair(w, v));
	flushEdge(v);
	e[v].push_back(std::make_pair(w, u));
}
inline bool valid(int x, int y, int z)
{
	return x >= 0 && x < maxn && y >= 0 && y < maxn && z >= 0 && z < maxn && str[z][y][x] == '#';
}
int main()
{
	memset(pos, -1, sizeof pos);
	for(int x = 0; x <= maxn * delta; ++x) if(delta <= std::__gcd(x, delta) * maxd)
		for(int y = 0; y <= maxn * delta; ++y) if(delta <= std::__gcd(y, delta) * maxd)
			for(int z = 0; z <= maxn * delta; ++z) if(delta <= std::__gcd(z, delta) * maxd)
				if(x % delta == 0 || y % delta == 0 || z % delta == 0)
					HashInsert((x * maxs + y) * maxs + z);
	// printf("%d\n", tot);
	for(int dx = 0; dx <= delta; ++dx) if(delta <= std::__gcd(dx, delta) * maxd)
		for(int dy = 0; dy <= delta; ++dy) if(delta <= std::__gcd(dy, delta) * maxd)
			if(!dx || dx == delta || !dy || dy == delta)
			{
				dir_seq[dir_tot][0] = dx;
				dir_seq[dir_tot][1] = dy;
				++dir_tot;
			}
	while(sp.read() && tp.read() && !(sp.isZero() && tp.isZero()))
	{
		for(int z = 0; z < maxn; ++z)
			for(int y = 0; y < maxn; ++y)
				scanf("%s", str[z][y]);
		// build edge
		++sysTim;
		for(int x = 0; x <= maxn; ++x)
			for(int y = 0; y <= maxn; ++y)
				for(int z = 0; z <= maxn; ++z)
				{
					// (x, y, z) -> (x, y + 1, z + 1)
					if(valid(x - 1, y, z) != valid(x, y, z))
					{
						for(int d1 = 0; d1 < dir_tot; ++d1)
						{
							Point P = (Point){x * delta, y * delta + dir_seq[d1][0], z * delta + dir_seq[d1][1]};
							int PID = P.getID();
							for(int d2 = d1 + 1; d2 < dir_tot; ++d2)
							{
								Point Q = (Point){x * delta, y * delta + dir_seq[d2][0], z * delta + dir_seq[d2][1]};
								addEdge(PID, Q.getID(), (P - Q).mode());
							}
						}
					}
					// (x, y, z) -> (x + 1, y, z + 1)
					if(valid(x, y - 1, z) != valid(x, y, z))
					{
						for(int d1 = 0; d1 < dir_tot; ++d1)
						{
							Point P = (Point){x * delta + dir_seq[d1][0], y * delta, z * delta + dir_seq[d1][1]};
							int PID = P.getID();
							for(int d2 = d1 + 1; d2 < dir_tot; ++d2)
							{
								Point Q = (Point){x * delta + dir_seq[d2][0], y * delta, z * delta + dir_seq[d2][1]};
								addEdge(PID, Q.getID(), (P - Q).mode());
							}
						}
					}
					// (x, y, z) -> (x + 1, y + 1, z)
					if(valid(x, y, z - 1) != valid(x, y, z))
					{
						for(int d1 = 0; d1 < dir_tot; ++d1)
						{
							Point P = (Point){x * delta + dir_seq[d1][0], y * delta + dir_seq[d1][1], z * delta};
							int PID = P.getID();
							for(int d2 = d1 + 1; d2 < dir_tot; ++d2)
							{
								Point Q = (Point){x * delta + dir_seq[d2][0], y * delta + dir_seq[d2][1], z * delta};
								addEdge(PID, Q.getID(), (P - Q).mode());
							}
						}
					}
				}
		// short path
		memset(vis, 0, sizeof vis);
		for(int i = 0; i < tot; ++i)
			dist[i] = 1e10;
		while(!Q.empty())
			Q.pop();
		dist[sp.getID()] = 0;
		Q.push(std::make_pair(dist[sp.getID()], sp.getID()));
		while(!Q.empty())
		{
			int u = Q.top().second;
			Q.pop();
			if(vis[u])
				continue;
			vis[u] = 1;
			flushEdge(u);
			for(std::vector<Edge>::iterator it = e[u].begin(); it != e[u].end(); ++it)
			{
				int v = it -> second;
				double w = it -> first;
				if(dist[v] > dist[u] + w)
				{
					dist[v] = dist[u] + w;
					Q.push(std::make_pair(dist[v], v));
				}
			}
		}
		printf("%.10f\n", dist[tp.getID()] / delta);
	}
	return 0;
}
