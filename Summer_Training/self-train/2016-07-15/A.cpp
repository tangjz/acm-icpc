#include <cstdio>
const int maxn = 100002;
int n, m, L[maxn], R[maxn];
int find(int fa[], int x)
{
	return x == fa[x] ? x : fa[x] = find(fa, fa[x]);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n + m)
	{
		L[0] = 0;
		for(int i = 1; i <= n; ++i)
			L[i] = R[i] = i;
		R[n + 1] = n + 1;
		while(m--)
		{
			int l, r, idx;
			scanf("%d%d", &l, &r);
			for(idx = find(L, r); idx >= l; idx = find(L, idx))
				L[idx] = find(L, idx - 1);
			if(idx)
				printf("%d", idx);
			else
				putchar('*');
			putchar(' ');
			for(idx = find(R, l); idx <= r; idx = find(R, idx))
				R[idx] = find(R, idx + 1);
			if(idx <= n)
				printf("%d", idx);
			else
				putchar('*');
			putchar('\n');
		}
		putchar('-');
		putchar('\n');
	}
	return 0;
}
