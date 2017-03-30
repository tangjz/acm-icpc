#include <stdio.h>
#include <cstring>
const int maxn = 5001, mod = 1000000007;
int n, pos[27], f[maxn][maxn];
char str[maxn];
void mod_add(int &x, int y)
{
	if((x += y) >= mod)
		x -= mod;
}
void mod_sub(int &x, int y)
{
	if((x -= y) < 0)
		x += mod;
}
int main()
{
	scanf("%d%s", &n, str);
	f[0][0] = 1;
	for(int i = 1; i <= n; ++i)
	{
		int pre = pos[str[i - 1]];
		pos[str[i - 1]] = i;
		memcpy(f[i], f[i - 1], (n + 1) * sizeof(int));
		for(int j = 1; j <= n; ++j)
		{
			mod_add(f[i][j], f[i][j - 1]);
			if(pre)
				mod_sub(f[i][j], f[pre][j - 1]);
		}
	}
	printf("%d\n", f[n][n]);
	return 0;
}
