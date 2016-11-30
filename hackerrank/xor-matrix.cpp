#include <stdio.h>
typedef long long LL;
const int maxn = 100001;
int n, f[2][maxn], cur, nxt = 1;
LL m;
inline int mod_add(int x, int y, int p)
{
	int z = x + y;
	return z < p ? z : z - p;
}
int main()
{
	scanf("%d%lld", &n, &m);
	--m;
	for(int i = 0; i < n; ++i)
		scanf("%d", f[cur] + i);
	for(int i = 0, d = 1; m; ++i, d = mod_add(d, d, n), m >>= 1)
	{
		if(~m & 1)
			continue;
		for(int j = 0; j < n; ++j)
			f[nxt][j] = f[cur][j] ^ f[cur][mod_add(j, d, n)];
		cur ^= 1;
		nxt ^= 1;
	}
	for(int i = 0; i < n; ++i)
		printf("%d%c", f[cur][i], " \n"[i == n - 1]);
	return 0;
}
