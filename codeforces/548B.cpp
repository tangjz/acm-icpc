#include <cstdio>
const int maxn = 501;
int n, m, q, mat[maxn][maxn], cnt[maxn], ans;
int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 1; i <= n; ++i)
	{
		int tmp = 0;
		for(int j = 1; j <= m; ++j)
		{
			scanf("%d", mat[i] + j);
			if(mat[i][j])
				++tmp;
			else
				tmp = 0;
			if(cnt[i] < tmp)
				cnt[i] = tmp;
		}
	}
	while(q--)
	{
		int x, y, tmp = 0;
		scanf("%d%d", &x, &y);
		mat[x][y] ^= 1;
		cnt[x] = 0;
		for(int j = 1; j <= m; ++j)
		{
			if(mat[x][j])
				++tmp;
			else
				tmp = 0;
			if(cnt[x] < tmp)
				cnt[x] = tmp;
		}
		tmp = 0;
		for(int i = 1; i <= n; ++i)
			if(tmp < cnt[i])
				tmp = cnt[i];
		printf("%d\n", tmp);
	}
	return 0;
}
