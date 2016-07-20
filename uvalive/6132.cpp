#include <cstdio>
const int maxb = 101, maxs = 201, mod = 1000000007;
int b, s, f[maxb][maxs][maxs];
void inline Add(int &x, int y)
{
	x += y;
	if(x >= mod)
		x -= mod;
}
int main()
{
	f[0][0][0] = 1;
	for(int i = 1; i <= 100; ++i)
		for(int j = 0; j <= 200; ++j)
			for(int k = 0; k <= 200; ++k)
			{
				if(j && k && k <= j)
					Add(f[i][j][k], f[i][j - 1][k - 1]);
				if(k * 2 <= j)
					Add(f[i][j][k], f[i - 1][j][k * 2]);
				if(k * 2 + 1 <= j)
					Add(f[i][j][k], f[i - 1][j][k * 2 + 1]);
			}
	while(scanf("%d%d", &s, &b) == 2)
		printf("%d\n", f[b][s][0]);
	return 0;
}
