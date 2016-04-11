#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 100001;
int t, n, a[maxn], c[maxn], f[maxn], seg[maxn << 1];
inline int seg_idx(int L, int R)
{
	return L + R | L != R;
}
void upd(int L, int R, int x, int v)
{
	int o = seg_idx(L, R);
	if(L == R)
	{
		seg[o] = v;
		return;
	}
	int M = L + R >> 1, lch = seg_idx(L, M), rch = seg_idx(M + 1, R);
	if(x <= M)
		upd(L, M, x, v);
	else
		upd(M + 1, R, x, v);
	seg[o] = std::min(seg[lch], seg[rch]);
}
int find(int L, int R, int v)
{
	while(L < R)
	{
		int M = L + R >> 1, lch = seg_idx(L, M);
		if(seg[lch] < v)
			R = M;
		else
			L = M + 1;
	}
	return L;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		for(int i = 1; i <= n; ++i)
			scanf("%d", c + i);
		memset(seg, 0, (n << 1) * sizeof(int));
		f[1] = 0;
		upd(0, n - 1, 0, 1);
		for(int i = 2; i <= n; ++i)
		{
			f[i] = find(0, n - 1, i - c[i]);
			upd(0, n - 1, f[i], i);
		}
		int sg = 0;
		for(int i = 1; i <= n; ++i)
		{
			// printf("%d%c", f[i], " \n"[i == n]);
			if(a[i] & 1)
				sg ^= f[i];
		}
		puts(sg ? "Win" : "Lose");
	}
	return 0;
}
