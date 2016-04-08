#include <map>
#include <cstring>
#include <algorithm>
using namespace std;
struct Node
{
	long long num; int number; bool flag;
	Node(void){}
	Node(long long x, int y, bool z) : num(x), number(y), flag(z) {}
	bool operator < (const Node &x) const { return num < x.num; }
} c[20001] = {};
pair<long long, long long> a[10001] = {}, b[10001] = {};
int n, k, f[30001][10] = {}, limit, cnt, key;
bool g[10][10] = {}, v[10] = {};
void change(const Node &x)
{
	if(!x.flag) --b[x.number].first;
	else --b[x.number].second;
}
void check(int visited[])
{
	int i, j;
	for(i = 1; i <= 9; ++i)
		for(j = 1; j <= 9; ++j)
			if(visited[i] && !visited[j] && g[i][j])
			{
				g[i][j] = g[j][i] = 0;
				--limit;
			}
}
void calc()
{
	int i, j, l, r;
	long long now = -1, L, R;
	for(i = 1; i <= n; ++i)
	{
		l = a[i].first % 10; r = a[i].second % 10;
		L = a[i].first / 10; R = a[i].second / 10;
		if(L != now && now > 0)
		{
			check(f[0]);
			memset(f[0],0,sizeof(f[0]));
		}
		if(L != R)
		{
			for(j = l; j <= 9; ++j) ++f[0][j];
			check(f[0]);
			memset(f[0],0,sizeof(f[0]));
			for(j = 1; j < r; ++j) ++f[0][j];
		}
		else
		    for(j = l; j < r; ++j) ++f[0][j];
		now = R;
	}
	check(f[0]);
}
bool work(int k)
{
	int i, j, p, q, num = 1;
	long long l, r, L, R, now = -1, pow = 1;
	map<long long ,int> hash;
	memset(f,0,sizeof(f));
	key = cnt = 0;
	for(i = 0; i < k; ++i) pow *= 10;
	for(i = 1; i <= n; ++i)
	{
		L = a[i].first / pow; R = a[i].second / pow;
		if(L || R)
		{
			l = a[i].first % pow; r = a[i].second % pow;
			b[++key] = make_pair(L + 1, R + 1);
			c[++cnt] = Node(l, key, false); c[++cnt] = Node(r, key, true);
		}
	}
	if(!key) return false;
	sort(c + 1, c + cnt + 1);
	for(p = 1;p <= cnt && !c[p].num; ++p) change(c[p]);
	for(i = 1; i <= key; ++i)
	{
		l = b[i].first % 10; r = b[i].second % 10;
		L = b[i].first / 10; R = b[i].second / 10;
		if(L != now && now > 0) hash[now] = num++;
		if(L != R)
		{
			for(j = l; j <= 9; ++j) ++f[num][j];
			hash[L] = num++;
			for(j = 1; j < r; ++j) ++f[num][j];
		}
		else
		    for(j = l; j < r; ++j) ++f[num][j];
		now = R;
	}
	hash[now] = num++;
	for(i = 1; i < num; ++i) check(f[i]);
	for( ; p <= cnt; p = q)
	{
		for(q = p; q <= cnt && c[q].num == c[p].num; ++q)
		{
			change(c[q]);
			if(!c[q].flag) now = b[c[q].number].first;
			else now = b[c[q].number].second;
			k = now % 10; now /= 10;
			if(!hash[now]) hash[now] = num++;
			now = hash[now];
			if(!c[q].flag) ++f[now][k];
			else --f[now][k];
		}
		for(i = 1; i < num; ++i) check(f[i]);
	}
	return true;
}
int main()
{
	int i, j;
	limit = 36;
	scanf("%d%d", &n, &k);
	for(i = 1; i <= n; ++i)
	{
		scanf("%d%d", &a[i].first, &a[i].second);
		++a[i].second;
	}
	memset(g, true, sizeof(g));
	calc();
	i = 1;
	while(i < k && work(i) && limit) ++i;
	for(i = 1; i <= 9; ++i)
		if(!v[i])
		{
			printf("%d", i);
			v[i] = true;
			for(j = 1; j <= 9; ++j)
				if(!v[j] && g[i][j])
				{
					printf("%d", j);
					v[j] = true;
				}
			putchar('\n');
		}
	return 0;
}
