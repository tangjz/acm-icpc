#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 1001, maxtr = 50;
int t, n, tim[maxn * maxn], col[maxn * maxn], tot;
vector<int> e[maxn * maxn];
struct ToSort
{
	int id;
	LL fz, fm;
	bool operator < (const ToSort &t) const
	{
		return fz * t.fm < fm * t.fz;
	}
} que[maxn];
struct Point
{
	int x, y;
	Point operator - (const Point &t) const
	{
		return (Point){x - t.x, y - t.y};
	}
	LL det(const Point &t) const
	{
		return (LL)x * t.y - (LL)y * t.x;
	}
	LL dot(const Point &t) const
	{
		return (LL)x * t.x + y * t.y;
	}
} pl[maxn][2], tr;
bool check(int trX, int trY)
{
	Point tr = (Point){trX, trY};
	for(int i = 0; i < n; ++i)
		if(!tr.det(pl[i][0] - pl[i][1]))
			return 0;
	return 1;
}
inline int idx(int x, int y)
{
	if(x > y)
		swap(x, y);
	return x * n + y;
}
bool color1()
{
	bool flag = 1;
	for(int i = 0; i < n && flag; ++i)
		for(int j = i + 1; j < n && flag; ++j)
			if(e[idx(i, j)].size())
				flag = 0;
	if(!flag)
		return 0;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(!col[idx(i, j)])
				col[idx(i, j)] = 1;
	return 1;
}
bool pfs(int u)
{
	int res = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(!col[*it] && !pfs(*it))
			return 0;
		res |= 1 << col[*it] - 1;
	}
	for(int i = 1; i <= 2; ++i)
		if(~(res >> i - 1) & 1)
		{
			col[u] = i;
			break;
		}
	return col[u];
}
bool color2()
{
	bool flag = 1;
	for(int i = 0; i < n && flag; ++i)
		for(int j = i + 1; j < n && flag; ++j)
			if(!col[idx(i, j)] && !pfs(idx(i, j)))
				flag = 0;
	if(flag)
		return 1;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(col[idx(i, j)] != -1)
				col[idx(i, j)] = 0;
	return 0;
}
void dfs(int u)
{
	int res = 0;
	for(vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it)
	{
		if(!col[*it])
			dfs(*it);
		res |= 1 << col[*it] - 1;
	}
	for(int i = 1; i <= 3; ++i)
		if(~(res >> i - 1) & 1)
		{
			col[u] = i;
			break;
		}
}
template<class T> inline void scan(T &x)
{
	int ch, flag;
	while(((ch = getchar()) < '0' || ch > '9') && (ch != '-'));
	flag = ch == '-';
	x = flag ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
	if(flag) x = -x;
}
template<class T> inline void print(T x, char ch = '\n')
{
	int len, out[2];
	if(x < 0) { putchar('-'); x = -x; }
	for(len = 0; x; x /= 10) out[len++] = x % 10;
	if(!len) out[len++] = 0;
	while(len) putchar('0' + out[--len]);
	if(ch) putchar(ch);
}
int main()
{
	scan(t);
	while(t--)
	{
		scan(n);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < 2; ++j)
				scan(pl[i][j].x), scan(pl[i][j].y);
		if(check(0, 1))
			tr = (Point){0, 1};
		else if(check(1, 0))
			tr = (Point){1, 0};
		else if(check(1, 1))
			tr = (Point){1, 1};
		else
		{
			bool flag = 0;
			for(int i = 1; i < maxtr && !flag; ++i)
				for(int j = i + 1; j < maxtr && !flag; ++j)
					if(__gcd(i, j) == 1 && check(i, j))
					{
						tr = (Point){i, j};
						flag = 1;
					}
		}
		for(int i = 0; i < n; ++i)
		{
			for(int j = 0; j < 2; ++j)
			{
				int xx = pl[i][j].det(tr), yy = pl[i][j].dot(tr);
				pl[i][j] = (Point){xx, yy};
			}
			if(pl[i][0].x > pl[i][1].x)
				swap(pl[i][0], pl[i][1]);
			//printf("%d %d %d %d\n", pl[i][0].x, pl[i][0].y, pl[i][1].x, pl[i][1].y);
		}
		for(int i = 0; i < n; ++i)
			for(int j = i + 1; j < n; ++j)
				e[idx(i, j)].clear();
		for(int i = 0; i < n; ++i)
		{
			tot = 0;
			for(int j = 0; j < n; ++j)
			{
				LL fm = (pl[i][0] - pl[i][1]).det(pl[j][0] - pl[j][1]);
				if(!fm)
				{
					col[idx(i, j)] = -1;
					continue;
				}
				col[idx(i, j)] = 0;
				LL fz = (pl[j][0] - pl[j][1]).det(pl[i][1] - pl[j][1]), r = __gcd(fz, fm);
				fz /= r;
				fm /= r;
				if(fm < 0)
				{
					fz = -fz;
					fm = -fm;
				}
				que[tot++] = (ToSort){j, fz, fm};
				//printf("ins %d by %d : %lld %lld\n", i, j, fz, fm);
			}
			sort(que, que + tot);
			for(int j = 1; j < tot; ++j)
			{
				e[idx(i, que[j - 1].id)].push_back(idx(i, que[j].id));
				//printf("edge on %d from %d to %d\n", i, que[j - 1].id, que[j].id);
			}
		}
		if(color1())
		{
			puts("1");
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
					print(col[idx(i, j)], " \n"[j == n - 1]);
		}
		else if(color2())
		{
			puts("2");
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
					print(col[idx(i, j)], " \n"[j == n - 1]);
			continue;
		}
		else
		{
			puts("3");
			for(int i = 0; i < n; ++i)
				for(int j = i + 1; j < n; ++j)
				{
					int id = idx(i, j);
					if(!col[id])
						dfs(id);
					print(col[id], " \n"[j == n - 1]);
			}
		}
	}
	return 0;
}

