#include <cstdio>
#include <cstring>
const int maxn = 500;
int n, m, t, p[maxn], e[maxn * maxn], sum, pos;
inline int idx(int i, int j)
{
	return i * n + j;
}
int main()
{
	scanf("%d%d%d", &n, &t, &m);
	for(int i = 0; i < t; ++i)
	{
		scanf("%d", p + i);
		--p[i];
	}
	memset(e, 0x3f, n * n * sizeof(int));
	for(int i = 0; i < n; ++i)
		e[idx(i, i)] = 0;
	for(int i = 0, u, v, w; i < m; ++i)
	{
		scanf("%d%d%d", &u, &v, &w);
		if(e[idx(--u, --v)] > w)
			e[idx(u, v)] = e[idx(v, u)] = w;
	}
	for(int k = 0; k < n; ++k)
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(e[idx(i, j)] > e[idx(i, k)] + e[idx(k, j)])
					e[idx(i, j)] = e[idx(i, k)] + e[idx(k, j)];
	sum = 0x3f3f3f3f;
	for(int i = 0; i < n; ++i)
	{
		int cnt = 0;
		for(int j = 0; j < t; ++j)
			cnt += e[idx(i, p[j])];
		if(sum > cnt)
		{
			sum = cnt;
			pos = i + 1;
		}
	}
	printf("%d\n", pos);
	return 0;
}
