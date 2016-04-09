#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100001, maxm = 200001;
int n, m, f[maxn], g[maxn], tot, bit[maxm], tim[maxm];
struct Node
{
	int idx, r, g, b;
	bool operator < (const Node &t) const
	{
		return g < t.g;
	}
} a[maxn], b[maxn];
void add(int x, int v)
{
	for( ; x < maxm; x += x & -x)
		if(tim[x] != tot)
		{
			bit[x] = v;
			tim[x] = tot;
		}
		else
			bit[x] += v;
}
int sum(int x)
{
	int ret = 0;
	for( ; x > 0; x -= x & -x)
		if(tim[x] == tot)
			ret += bit[x];
	return ret;
}
void solve(int L, int R)
{
	if(L == R)
		return;
	int M = L + R >> 1;
	solve(L, M);
	solve(M + 1, R);
	++tot;
	int sz = 0;
	for(int i = L, j = M + 1; i <= M || j <= R; )
		if(i > M || j <= R && a[j] < a[i])
		{
			f[a[j].idx] += sum(a[j].b);
			b[sz++] = a[j++];
		}
		else
		{
			add(a[i].b, 1);
			b[sz++] = a[i++];
		}
	memcpy(a + L, b, sz * sizeof(Node));
}
bool cmp(const Node &x, const Node &y)
{
	if(x.r != y.r)
		return x.r < y.r;
	if(x.g != y.g)
		return x.g < y.g;
	return x.b < y.b;
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
	{
		a[i].idx = i;
		scanf("%d%d%d", &a[i].r, &a[i].g, &a[i].b);
	}
	sort(a, a + n, cmp);
	for(int i = 0, j; i < n; i = j)
	{
		for(j = i + 1; j < n && !cmp(a[i], a[j]); ++j);
		for(int k = i; k < j; ++k)
			f[a[k].idx] += j - k - 1;
	}
	solve(0, n - 1);
	for(int i = 0; i < n; ++i)
		++g[f[i]];
	for(int i = 0; i < n; ++i)
		printf("%d\n", g[i]);
	return 0;
}
