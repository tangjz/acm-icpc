#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 1100001, maxp = 6, pr[maxp] = {2, 3, 5, 7, 11, 13}, INF = 0x3f3f3f3f;
int n, f[2][maxn];
int F(int i, int j)
{
	int &ret = f[i][j];
	if(ret != -1)
		return ret;
	ret = INF;
	if(i == 1)
		for(int k = 1; k <= 4; ++k)
			ret = std::min(ret, F(0, j + k) + k);
	else
		for(int k = 0; k < maxp; ++k)
		{
			if(j % pr[k])
				continue;
			int v = j / pr[k];
			ret = std::min(ret, std::min(F(0, v), F(1, v)) + pr[k]);
		}
	return ret;
}
int main()
{
	scanf("%d", &n);
	memset(f, -1, sizeof f);
	f[0][1] = f[1][1] = 0;
	printf("%d\n", std::min(F(0, n), F(1, n)));
	return 0;
}
