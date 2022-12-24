#include <stdio.h>
const int maxn = 201;
int n, m, mat[maxn][maxn];
void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				scanf("%d", &mat[i][j]);
				mat[i][j] %= m;
				if(mat[i][j] < 0)
					mat[i][j] += m;
			}
		int ret = 1;
		for(int i = 0; i < n; ++i)
		{
			for(int j = i + 1; j < n; ++j)
				while(mat[j][i])//gcd ~ logn
				{
					int d = mat[i][i] / mat[j][i];
					for(int k = i; k < n; ++k)
					{
						mat[i][k] -= (long long)d * mat[j][k] % m;
						if(mat[i][k] < 0)
							mat[i][k] += m;
						swap(mat[i][k], mat[j][k]);
					}
					ret = -ret;
				}
			ret = (long long)ret * mat[i][i] % m;
		}
		if(ret < 0)
			ret += m;
		printf("%d\n", ret);
	}
	return 0;
}
