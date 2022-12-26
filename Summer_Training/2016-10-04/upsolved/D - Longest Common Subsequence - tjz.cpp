#include <stdio.h>
#include <cstring>
const int maxn = 3001;
int n, m, p, a[maxn], f[2][maxn], cur, pre = 1;
int tim[maxn], cnt[maxn], lim[maxn], tot, L[maxn], R[maxn];
int main()
{
	scanf("%d%d%d", &n, &m, &p);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	while(m--)
	{
		int len, x;
		scanf("%d", &len);
		memset(tim + 1, 0, p * sizeof(int));
		memset(lim + 1, 0, p * sizeof(int));
		for(int i = 0; i < len; ++i)
		{
			scanf("%d", &x);
			++lim[x];
		}
		cur ^= 1;
		pre ^= 1;
		memcpy(f[cur] + 1, f[pre] + 1, n * sizeof(int));
		L[0] = R[0] = 0;
		for(int i = 1; i <= n; ++i)
		{
			L[i] = 0;
			R[i] = R[0];
			L[R[0]] = i;
			R[0] = i;
			for(int j = R[0], w = 0; j; j = R[j])
			{
				if(tim[a[j]] != i)
				{
					tim[a[j]] = i;
					cnt[a[j]] = 0;
				}
				if(cnt[a[j]] < lim[a[j]])
				{
					++cnt[a[j]];
					if(f[cur][i] < f[pre][j - 1] + (++w))
						f[cur][i] = f[pre][j - 1] + w;
				}
				else
				{
					L[R[j]] = L[j];
					R[L[j]] = R[j];
					j = L[j];
				}
			}
			// printf("%d%c", f[cur][i], " \n"[i == n]);
		}
	}
	printf("%d\n", f[cur][n]);
	return 0;
}
