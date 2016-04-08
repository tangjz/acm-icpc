#include <cstdio>
const int maxn = 100;
int n, m, mat[maxn][maxn];
inline void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}
inline void scan(int &x)
{
    static char ch;
    while((ch = getchar()) < '0' || ch > '9');
    x = ch - '0';
    while((ch = getchar()) >= '0' && ch <= '9')
        x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	scan(n), scan(m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
		{
			scan(mat[i][j]);
			mat[i][j] %= m;
		}
	int ret = 1;
	for(int i = 0; i < n; ++i)
	{
		for(int j = i + 1; j < n; ++j)
			while(mat[j][i])//gcd ~ logm
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
	return 0;
}
