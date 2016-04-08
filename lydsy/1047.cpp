#include <cstdio>
const int maxa = 1001, maxb = 1001, maxn = 11, INF = 0x3f3f3f3f;
int a, b, n, val[maxa][maxb], maxv[maxa][maxb], minv[maxa][maxb], que[maxn][2], l, r, ans;
int main()
{
	scanf("%d%d%d", &a, &b, &n);
	for(int i = 0; i < a; ++i)
		for(int j = 0; j < b; ++j)
			scanf("%d", &val[i][j]);
	for(int i = 0; i < a; ++i)
	{
		l = r = 0;
		for(int j = 0; j < b; ++j)
		{
			while(l < r && que[r - 1][1] <= val[i][j])
				--r;
			que[r][0] = j;
			que[r++][1] = val[i][j];
			if(j - que[l][0] >= n)
				++l;
			maxv[i][j] = que[l][1];
		}
		l = r = 0;
		for(int j = 0; j < b; ++j)
		{
			while(l < r && que[r - 1][1] >= val[i][j])
				--r;
			que[r][0] = j;
			que[r++][1] = val[i][j];
			if(j - que[l][0] >= n)
				++l;
			minv[i][j] = que[l][1];
		}
	}
	for(int i = 0; i < b; ++i)
	{
		l = r = 0;
		for(int j = 0; j < a; ++j)
		{
			while(l < r && que[r - 1][1] <= maxv[j][i])
				--r;
			que[r][0] = j;
			que[r++][1] = maxv[j][i];
			if(j - que[l][0] >= n)
				++l;
			maxv[j][i] = que[l][1];
		}
		l = r = 0;
		for(int j = 0; j < a; ++j)
		{
			while(l < r && que[r - 1][1] >= minv[j][i])
				--r;
			que[r][0] = j;
			que[r++][1] = minv[j][i];
			if(j - que[l][0] >= n)
				++l;
			minv[j][i] = que[l][1];
		}
	}
	ans = INF;
	for(int i = n - 1; i < a; ++i)
		for(int j = n - 1; j < b; ++j)
			if(ans > maxv[i][j] - minv[i][j])
				ans = maxv[i][j] - minv[i][j];
	printf("%d\n", ans);
	return 0;
}
