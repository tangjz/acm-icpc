#include <set>
#include <map>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
const int maxn = 2010, maxs = 2000001, mod = 1000000007;
int n, f[maxn], g[maxn], seg[maxn << 1], sum, tot, ans[maxs][2];
inline int idx(int L, int R)
{
	return L + R | L != R;
}
void init(int L, int R)
{
	int o = idx(L, R);
	if(L == R)
	{
		seg[o] = f[L];
		return;
	}
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	init(L, M);
	init(M + 1, R);
	seg[o] = min(seg[lch], seg[rch]);
}
void upd(int L, int R, int x, int v)
{
	int o = idx(L, R);
	if(L == R)
	{
		seg[o] = v;
		return;
	}
	int M = L + R >> 1, lch = idx(L, M), rch = idx(M + 1, R);
	if(x <= M)
		upd(L, M, x, v);
	else
		upd(M + 1, R, x, v);
	seg[o] = min(seg[lch], seg[rch]);
}
int que(int L, int R, int l, int r)
{
	int o = idx(L, R);
	if(l <= L && R <= r)
		return seg[o];
	int M = L + R >> 1, ret = n;
	if(l <= M)
		ret = min(ret, que(L, M, l, r));
	if(r > M)
		ret = min(ret, que(M + 1, R, l, r));
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", f + i);
	for(int i = 1; i <= n; ++i)
	{
		int x;
		scanf("%d", &x);
		g[x] = i;
	}
	for(int i = 1; i <= n; ++i)
		f[i] = g[f[i]];
	for(int i = 1; i <= n; ++i)
		g[f[i]] = i;
	init(1, n);
	for(int i = n; i >= 1; --i)
	{
		int j = g[i];
		sum += i - g[i];
		while(j != i)
		{
			int k = g[que(1, n, j + 1, i)];
			swap(f[j], f[k]);
			swap(g[f[j]], g[f[k]]);
			upd(1, n, j, f[j]);
			upd(1, n, k, f[k]);
			ans[tot][0] = j;
			ans[tot++][1] = k;
			j = k;
		}
	}
	printf("%d\n%d\n", sum, tot);
	for(int i = 0; i < tot; ++i)
		printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
