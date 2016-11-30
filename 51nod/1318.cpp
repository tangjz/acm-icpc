#include <map>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 401, maxp = maxn * 9, INF = 0x3f3f3f3f;
int tot, pr[maxp];
struct Limit
{
	int typ, x, y, z; // lcm(0), gcd(1) | leq(0), geq(1)
	bool operator < (const Limit &t) const
	{
		return make_pair(make_pair(typ, x), make_pair(y, z)) < make_pair(make_pair(t.typ, t.x), make_pair(t.y, t.z));
	}
	bool operator == (const Limit &t) const
	{
		return make_pair(make_pair(typ, x), make_pair(y, z)) == make_pair(make_pair(t.typ, t.x), make_pair(t.y, t.z));
	}
} lim[maxn], a[maxn];
vector<int> e[maxn << 1], r[maxn << 1];
int t, n, m, seq[maxn << 1], scnt, sno[maxn << 1];
bool vis[maxn << 1];
void pfs1(int u)
{
	vis[u] = 1;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
		if(!vis[*it])
			pfs1(*it);
	seq[scnt++] = u;
}
void pfs2(int u)
{
	vis[u] = 1;
	sno[u] = scnt;
	for(vector<int>::iterator it = r[u].begin(); it != r[u].end(); ++it)
		if(!vis[*it])
			pfs2(*it);
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		tot = 0;
		for(int i = 0; i < m; ++i)
		{
			char op[2];
			int a, b, c;
			scanf("%s%d%d%d", op, &a, &b, &c);
			lim[i] = (Limit){op[0] == 'G', a, b, c};
			for(int i = 2; i * i <= c; ++i)
				if(c % i == 0)
				{
					for(c /= i; c % i == 0; c /= i);
					pr[tot++] = i;
				}
			if(c > 1)
				pr[tot++] = c;
		}
		sort(pr, pr + tot);
		tot = unique(pr, pr + tot) - pr;
		bool flag = 1;
		for(int pdx = 0; pdx < tot && flag; ++pdx)
		{
			n = 0;
			for(int i = 0; i < m; ++i)
			{
				int cnt = 0;
				for(int tmp = lim[i].z; tmp % pr[pdx] == 0; tmp /= pr[pdx], ++cnt);
				Limit tmp = lim[i];
				tmp.z = cnt;
				a[n++] = tmp;
				swap(tmp.x, tmp.y);
				a[n++] = tmp;
			}
			sort(a, a + n);
			n = unique(a, a + n) - a;
			for(int i = 0; i < m; ++i)
			{
				int cnt = 0;
				for(int tmp = lim[i].z; tmp % pr[pdx] == 0; tmp /= pr[pdx], ++cnt);
				Limit tmp = lim[i];
				tmp.z = cnt;
				int idx = lower_bound(a, a + n, tmp) - a;
				swap(tmp.x, tmp.y);
				int jdx = lower_bound(a, a + n, tmp) - a;
				e[n + idx].push_back(jdx);
				r[jdx].push_back(n + idx);
				e[n + jdx].push_back(idx);
				r[idx].push_back(n + jdx);
			}
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
				{
					bool chk = 1;
					if(chk)
					{ // check a[i].x
						int L = a[i].z, R = a[i].z;
						if(a[i].x == a[j].x)
						{
							L = max(L, a[j].z);
							R = min(R, a[j].z);
						}
						if(a[i].x == a[j].y)
						{
							if(a[j].typ)
								L = max(L, a[j].z);
							else
								R = min(R, a[j].z);
						}
						if(L > R)
							chk = 0;
					}
					if(chk)
					{ // check a[i].y
						int L = a[i].typ ? a[i].z : 0, R = a[i].typ ? INF : a[i].z;
						if(a[i].y == a[j].x)
						{
							L = max(L, a[j].z);
							R = min(R, a[j].z);
						}
						if(a[i].y == a[j].y)
						{
							if(a[j].typ)
								L = max(L, a[j].z);
							else
								R = min(R, a[j].z);
						}
						if(L > R)
							chk = 0;
					}
					if(!chk)
					{
						e[i].push_back(n + j);
						r[n + j].push_back(i);
						e[j].push_back(n + i);
						r[n + i].push_back(j);
					}
				}
			scnt = 0;
			memset(vis, 0, (n << 1) * sizeof(bool));
			for(int i = 0; i < n << 1; ++i)
				if(!vis[i])
					pfs1(i);
			scnt = 0;
			memset(vis, 0, (n << 1) * sizeof(bool));
			for(int i = (n << 1) - 1; i >= 0; --i)
				if(!vis[seq[i]])
				{
					pfs2(seq[i]);
					++scnt;
				}
			for(int i = 0; i < n && flag; ++i)
				flag &= sno[i] != sno[n + i];
			for(int i = 0; i < n << 1; ++i)
			{
				vector<int>().swap(e[i]);
				vector<int>().swap(r[i]);
			}
		}
		puts(flag ? "Solution exists" : "Solution does not exist");
	}
	return 0;
}
