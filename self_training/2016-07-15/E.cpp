#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 20001, INF = 0x3f3f3f3f;
map<int, int> Hash;
int n, m, q, pos[maxn], a[maxn], b[maxn], que[maxn], L, R;
vector<pair<int, int> > e[maxn];
inline int getID(int x)
{
	if(Hash.count(x))
		return Hash[x];
	vector<pair<int, int> >().swap(e[n]);
	return Hash[x] = n++;
}
int main()
{
	while(scanf("%d%d", &m, &q) == 2 && m + q)
	{
		n = 0;
		map<int, int>().swap(Hash);
		while(m--)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u = getID(u);
			v = getID(v);
			if(u == v)
				w <<= 1;
			e[u].push_back(make_pair(v, w));
			e[v].push_back(make_pair(u, w));
		}
		memset(pos, 0, n * sizeof(int));
		for(int i = 0, col = 0; i < n; ++i)
		{
			if(pos[i])
				continue;
			++col;
			int x = INF;
			L = R = 0;
			pos[i] = col;
			a[i] = 1;
			b[i] = 0;
			que[R++] = i;
			while(L < R)
			{
				int u = que[L++];
				for(vector<pair<int, int> >::iterator it = e[u].begin(); it != e[u].end(); ++it)
				{
					int v = it -> first, w = it -> second;
					if(!pos[v])
					{
						pos[v] = col;
						a[v] = -a[u];
						b[v] = w - b[u];
						que[R++] = v;
					}
					else if(!(a[u] + a[v] == 0 && b[u] + b[v] == w))
					{
						if(a[u] + a[v] != 0 && (~(w - b[u] - b[v]) & 1))
						{
							int y = (w - b[u] - b[v]) / (a[u] + a[v]);
							if(x == INF)
								x = y;
							else if(x != y)
								x = -INF;
						}
						else
							x = -INF;
					}
				}
			}
			if(x == -INF)
				for(int j = 0; j < R; ++j)
					a[que[j]] = x;
			else if(x != INF)
				for(int j = 0; j < R; ++j)
				{
					b[que[j]] += a[que[j]] * x;
					a[que[j]] = 0;
				}
		}
		while(q--)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			if(!(Hash.count(u) && Hash.count(v)))
				putchar('*');
			else
			{
				u = getID(u);
				v = getID(v);
				if(pos[u] != pos[v])
				{
					if(a[u] || a[v])
						putchar('*');
					else
						printf("%d", b[u] + b[v]);
				}
				else
				{
					if(a[u] + a[v] != 0)
						putchar('*');
					else if(u != v)
						printf("%d", b[u] + b[v]);
					else
						printf("%d", b[u]);
				}
			}
			putchar('\n');
		}
		putchar('-');
		putchar('\n');
	}
	return 0;
}
