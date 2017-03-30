#include <stdio.h>
#include <cstring>
const int maxn = 100, maxm = maxn * maxn * maxn + 2, maxd = 10;
int t, n, e[maxn][maxn], cnt[maxm], L[maxm], R[maxm], S, T, ans;
inline void upd(int id, int flag)
{
	if(cnt[id] == 2)
	{
		L[R[id]] = L[id];
		R[L[id]] = R[id];
	}
	flag ? ++cnt[id] : --cnt[id];
	if(cnt[id] == 2)
	{
		L[id] = L[T];
		R[id] = T;
		R[L[T]] = id;
		L[T] = id;
	}
}
inline int idx(int x, int y, int z)
{
	return (x * n + y) * n + z;
}
void dfs(int dep)
{
	if(R[S] == T)
	{
		ans = dep;
		return;
	}
	if(dep >= ans || dep == maxd)
		return;
	int p[3], i, j, k;
	for(i = 2, j = R[S]; i >= 0; --i)
	{
		p[i] = j % n;
		j /= n;
	}
	for(i = 0; i < 3; ++i)
		for(j = i + 1; j < 3; ++j)
		{
			e[p[i]][p[j]] ^= 1;
			for(k = 0; k < p[i]; ++k)
				upd(idx(k, p[i], p[j]), e[p[i]][p[j]]);
			for(++k; k < p[j]; ++k)
				upd(idx(p[i], k, p[j]), e[p[i]][p[j]]);
			for(++k; k < n; ++k)
				upd(idx(p[i], p[j], k), e[p[i]][p[j]]);
			dfs(dep + 1);
			e[p[i]][p[j]] ^= 1;
			for(k = 0; k < p[i]; ++k)
				upd(idx(k, p[i], p[j]), e[p[i]][p[j]]);
			for(++k; k < p[j]; ++k)
				upd(idx(p[i], k, p[j]), e[p[i]][p[j]]);
			for(++k; k < n; ++k)
				upd(idx(p[i], p[j], k), e[p[i]][p[j]]);
		}
}
int main()
{
	int i, j, k;
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d", &n);
		S = n * n * n, T = S + 1;
		R[S] = T, L[T] = S;
		memset(cnt, 0, S * sizeof(int));
		for(i = 0; i < n; ++i)
			for(j = 0; j < n; ++j)
			{
				scanf("%d", e[i] + j);
				if(i >= j || !e[i][j])
					continue;
				for(k = 0; k < i; ++k)
					++cnt[idx(k, i, j)];
				for(++k; k < j; ++k)
					++cnt[idx(i, k, j)];
				for(++k; k < n; ++k)
					++cnt[idx(i, j, k)];
			}
		for(i = 0; i < n; ++i)
			for(j = i + 1; j < n; ++j)
				for(k = j + 1; k < n; ++k)
				{
					int id = idx(i, j, k);
					if(cnt[id] != 2)
						continue;
					L[id] = L[T];
					R[id] = T;
					R[L[T]] = id;
					L[T] = id;
				}
		ans = maxd + 1;
		dfs(0);
		printf("Case #%d: %d\n", Case, ans <= maxd ? ans : -1);
	}
	return 0;
}
