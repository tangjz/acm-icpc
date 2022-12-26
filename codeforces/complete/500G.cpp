#include <cstdio>
typedef long long LL;
const int maxn = 200001, maxf = 19;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;
int n, q, tot, lnk[maxn], dep[maxn], fa[maxn][maxf];
struct Edge
{
	int v, nxt;
} e[maxn << 1];
template<class T> void swap(T& x, T& y)
{
	const T t = x;
	x = y;
	y = t;
}
template<class T> const T& min(const T& x, const T& y)
{
	return x < y ? x : y;
}
void dfs(int u)
{
	for(int it = lnk[u]; it; it = e[it].nxt)
	{
		int &v = e[it].v;
		if(v == fa[u][0])
			continue;
		dep[v] = dep[u] + 1;
		fa[v][0] = u;
		for(int i = 1; fa[v][i - 1]; ++i)
			fa[v][i] = fa[fa[v][i - 1]][i - 1];
		dfs(v);
	}
}
int deeper(int u, int v)
{
	return dep[u] < dep[v] ? v : u;
}
int lca(int u, int v)
{
	if(dep[u] > dep[v])
		swap(u, v);
	for(int i = 0, j = dep[v] - dep[u]; j; ++i, j >>= 1)
		if(j & 1)
			v = fa[v][i];
	if(u == v)
		return u;
	for(int i = maxf - 1; i >= 0; --i)
		if(fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
int dist(int u, int v)
{
	return dep[u] + dep[v] - (dep[lca(u, v)] << 1);
}
int gcd(int x, int y)
{
	return y ? gcd(y, x % y) : x;
}
void exgcd(int a, int b, int &x, int &y)
{
	if(!b)
	{
		x = 1;
		y = 0;
		return;
	}
	exgcd(b, a % b, y, x);
	y -= x * (a / b);
}
LL Case1(int t1, int d1, int t2, int d2) // same : t1 * x = d2 - d1 (mod t2)
{
	int g = gcd(t1, t2), r = (d2 - d1) % t2;
	if(r < 0)
		r += t2;
	if(r % g != 0)
		return INF;
	int x, y;
	t1 /= g;
	t2 /= g;
	r /= g;
	exgcd(t1, t2, x, y);//t1 * x = 1 (mod t2), gcd(t1, t2) = 1
	if(x < 0)
		x += t2;
	x = (LL)x * r % t2;
	return (LL)x * t1 * g + d1;
}
int AMAC(int m, int d, int l, int r) // l <= m * x mod d <= r
{
	if(l % d == 0)
		return l / d;
	if(l / d != r / d)
		return l / d + 1;
	int g = gcd(m, d);
	if(l % g != 0 && l / g == r / g)
		return -1;
	int res = AMAC(d, m % d, -r % d + d, -l % d + d);
	if(res == -1)
		return -1;
	return ((LL)res * m + l - 1) / d + 1;
}
LL Case2(int t1, int d1, int t2, int d2, int dd) //diff : d2 - d1 - dd <= t1 * x <= d2 - d1 + dd (mod t2)
{
	int m = t2, d = t1, l = (d2 - d1 - dd) % t2, r = (d2 - d1 + dd) % t2;
	if(l < 0)
		l += t2;
	if(r < 0)
		r += t2;
	if(l & 1)
		return INF;
	if(t2 == dd * 2 || l > r || l == 0)
		return d1 + r / 2;
	if(!(d %= m))
		return INF;
	LL res = AMAC(m, d, l, r);
	if(res == -1)
		return INF;
	return t1 * res + d1 + dd - (t1 * res % t2 - l) / 2;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1, u, v; i < n; ++i)
	{
		scanf("%d%d", &u, &v);
		e[++tot] = (Edge){v, lnk[u]};
		lnk[u] = tot;
		e[++tot] = (Edge){u, lnk[v]};
		lnk[v] = tot;
	}
	dfs(1);
	scanf("%d", &q);
	while(q--)
	{
		int u, v, x, y;
		scanf("%d%d%d%d", &u, &v, &x, &y);
		int px = deeper(lca(u, x), lca(v, x));//x path in u -> v [px -> lca]
		int py = deeper(lca(u, y), lca(v, y));//y path in u -> v [py -> lca]
		int pp = deeper(lca(u, v), lca(x, y));//common path is px -> pp -> py
		if(dep[px] < dep[pp] && dep[py] < dep[pp])
		{
			puts("-1");
			continue;
		}
		if(dep[px] < dep[pp])
			px = pp;
		else if(dep[py] < dep[pp])
			py = pp;
		int f1 = dist(u, v) << 1, f2 = dist(x, y) << 1, d = dist(px, py);
		int t1 = dist(u, px), t2 = dist(u, py), t3 = dist(x, px), t4 = dist(x, py);
		if(t1 <= t2)
			t2 = f1 - t2;
		else
			t1 = f1 - t1;
		if(t3 <= t4)
			t4 = f2 - t4;
		else
			t3 = f2 - t3;
		LL ans = min(min(Case1(f1, t1, f2, t3), Case2(f1, t1, f2, t4, d)),
					 min(Case1(f1, t2, f2, t4), Case2(f1, t2, f2, t3, d)));
		if(ans == INF)
			puts("-1");
		else
			printf("%I64d\n", ans);
	}
	return 0;
}
