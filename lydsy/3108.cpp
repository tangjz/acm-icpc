/*
 * 对于任意点k 指向它的点 具有相同的性质 : 指向相同的点 不指向相同的点
 */
#include <cstdio>
#include <cstring>
int n, m;
bool g[301][301];
bool check()
{
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
		{
			bool flag1 = 0, flag2 = 0;
			for(int k = 0; k < n; ++k)
			{
				flag1 |= g[i][k] & g[j][k];
				flag2 |= g[i][k] ^ g[j][k];
				if(flag1 & flag2) return 0;
			}
		}
	return 1;
}
int main()
{
	int i, j, t;
	scanf("%d", &t);
	while(t--)
	{
		memset(g, 0, sizeof(g));
		scanf("%d%d", &n, &m);
		while(m--) { scanf("%d%d", &i, &j); g[i][j] = 1; }
		printf("%s\n", check() ? "Yes" : "No");
	}
	return 0;
}
