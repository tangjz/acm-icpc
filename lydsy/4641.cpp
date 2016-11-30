#include <stdio.h>
#include <cstring>
const int maxn = 1000001;
int t, p, n, m, a[maxn], b[maxn], pos[maxn], f[maxn], sz, out[maxn];
inline bool chk(int *pat, int pid, int *tex, int tid)
{
	return pat[pid] < 0 ? (tex[tid] < 0 || tex[tid] > pid) : pat[pid] == tex[tid];
}
int main()
{
	scanf("%d%d", &t, &p);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(pos + 1, -1, p * sizeof(int));
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", a + i);
			int pr = pos[a[i]];
			pos[a[i]] = i;
			a[i] = pr < 0 ? -1 : i - pr;
		}
		memset(pos + 1, -1, p * sizeof(int));
		for(int i = 0; i < m; ++i)
		{
			scanf("%d", b + i);
			int pr = pos[b[i]];
			pos[b[i]] = i;
			b[i] = pr < 0 ? -1 : i - pr;
		}
		for(int i = 1, j = 0; i < m; ++i)
		{
			for( ; j && !chk(b, j, b, i); j = f[j]);
			if(chk(b, j, b, i))
				++j;
			f[i + 1] = j;
		}
		sz = 0;
		for(int i = 0, j = 0; i < n; ++i)
		{
			for( ; j && !chk(b, j, a, i); j = f[j]);
			if(chk(b, j, a, i))
				++j;
			if(j == m)
			{
				out[sz++] = i - m + 2;
				j = f[j];
			}
		}
		printf("%d\n", sz);
		for(int i = 0; i < sz; ++i)
			printf("%d ", out[i]);
		putchar('\n');
	}
	return 0;
}
