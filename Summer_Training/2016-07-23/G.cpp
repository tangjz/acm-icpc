#include <cstdio>
#include <algorithm>
const int n = 4, maxd = 4, dx[maxd] = {-1, 0, 1, 0}, dy[maxd] = {0, -1, 0, 1}, INF = 0x3f3f3f3f;
int t, x[n], y[n], px[n], py[n], perm[n], dir[n], seg[4][2], len[4], pos[4];
bool dfs(int dep, int lim)
{
	if(dep == n)
	{
		for(int i = 0; i < 4; ++i)
		{
			seg[i][0] = -INF;
			seg[i][1] = INF;
		}
		for(int i = 0; i < n; ++i)
		{
			int ox = perm[i] & 1, oy = (perm[i] >> 1) & 1, L, R;
			L = x[i], R = x[i] + dx[dir[i]] * lim;
			if(L > R)
				std::swap(L, R);
			seg[ox][0] = std::max(seg[ox][0], L);
			seg[ox][1] = std::min(seg[ox][1], R);
			L = y[i], R = y[i] + dy[dir[i]] * lim;
			if(L > R)
				std::swap(L, R);
			seg[2 + oy][0] = std::max(seg[2 + oy][0], L);
			seg[2 + oy][1] = std::min(seg[2 + oy][1], R);
		}
		for(int i = 0; i < 4; ++i)
			if(seg[i][0] > seg[i][1])
				return 0;
		for(int i = 0; i < 4; ++i)
			len[i] = (seg[i][1] - seg[i ^ 1][0]) * (i & 1 ? 1 : -1);
		if((len[0] = std::max(len[0], len[2])) > (len[1] = std::min(len[1], len[3])))
			return 0;
		for(int i = 0; i < 4; ++i)
			pos[i] = i & 1 ? pos[i - 1] + len[0] : std::max(seg[i][0], seg[i ^ 1][0] - len[0]);
		for(int i = 0; i < n; ++i)
		{
			px[i] = pos[perm[i] & 1];
			py[i] = pos[2 + ((perm[i] >> 1) & 1)];
		}
		return 1;
	}
	for(int i = 0; i < maxd; ++i)
	{
		dir[dep] = i;
		if(dfs(dep + 1, lim))
			return 1;
	}
	return 0;
}
bool check(int lim)
{
	for(int i = 0; i < n; ++i)
		perm[i] = i;
	do
	{
		if(dfs(0, lim))
			return 1;
	} while(std::next_permutation(perm, perm + n));
	return 0;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		for(int i = 0; i < n; ++i)
			scanf("%d%d", x + i, y + i);
		int L = 0, R = INF;
		while(L < R)
		{
			int M = L + R >> 1;
			if(check(M))
				R = M;
			else
				L = M + 1;
		}
		if(check(L))
		{
			printf("%d\n", L);
			for(int i = 0; i < 4; ++i)
				printf("%d %d\n", px[i], py[i]);
		}
		else
			puts("-1");
	}
	return 0;
}
