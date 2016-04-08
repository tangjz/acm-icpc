#include <cstdio>
#include <algorithm>
using namespace std;
const int maxk = 23, maxn = 33;
int n, k, x, f[maxn][maxk];
int main()
{
	while(scanf("%d%d%d", &k, &x, &n) == 3)
	{
		int last = 0;
		for(int i = 0; i < k; ++i)
		{
			f[0][i] = x & 1;
			last += f[0][i] == 1;
			x >>= 1;
		}
		for(int i = 1; i <= n; ++i)
		{
			int cnt = 0, now = 0;
			for(int j = 0; j < k; ++j)
				f[i][j] = f[i - 1][j];
			for(int j = 0; j < k; ++j)
				if(f[i][j] == 1)
				{
					f[i][j] = 0;
					++cnt;
				}
				else
				{
					f[i][j] = 1;
					++cnt;
					break;
				}
			for(int j = 0; j < k; ++j)
				now += f[i][j] == 1;
			printf("%d\n", cnt + now - last);
			last = now;
		}
	}
	return 0;
}
