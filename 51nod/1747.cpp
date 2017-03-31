#include <stdio.h>
//#include <cassert>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxt = 11, maxn = 201, mod = 998244353;
int inv[maxn << 1 | 1], b[maxn], c[maxn], t, n, mat[maxn][maxn + 2];
inline int mod_inv(int x)
{
	return x < maxn << 1 ? inv[x] : mod - mod / x * (LL)mod_inv(mod % x) % mod;
}
int main()
{
	inv[1] = 1;
	for(int i = 2; i < maxn << 1; ++i)
		inv[i] = mod - mod / i * (LL)inv[mod % i] % mod;
	b[0] = 1, c[0] = mod - 1;
	for(int i = 1; i < maxn; ++i)
	{
		b[i] = (1 + (LL)(mod - i) * b[i - 1]) % mod;
		c[i] = (LL)(mod - i) * c[i - 1] % mod;
	}
	scanf("%d", &t); //assert(scanf("%d", &t) == 1 && 1 <= t && t < maxt);
	while(t--)
	{
		scanf("%d", &n); //assert(scanf("%d", &n) == 1 && 0 <= n && n < maxn);
		for(int i = 0; i <= n; ++i)
		{
			for(int j = 0; j <= n; ++j)
				mat[i][j] = inv[i + j + 1];
			mat[i][n + 1] = b[i];
			mat[i][n + 2] = c[i];
		}
		for(int i = 0; i <= n; ++i)
		{
			if(!mat[i][i])
				for(int j = i + 1; j <= n; ++j)
					if(mat[j][i])
					{
						for(int k = i; k <= n + 2; ++k)
							swap(mat[i][k], mat[j][k]);
						break;
					}
			//assert(mat[i][i]);
			int invi = mod_inv(mat[i][i]);
			for(int j = i; j <= n + 2; ++j)
				mat[i][j] = (LL)mat[i][j] * invi % mod;
			for(int j = 0; j <= n; ++j)
				if(i != j && mat[j][i])
				{
					int d = mat[j][i];
					for(int k = i; k <= n + 2; ++k)
					{
						mat[j][k] -= (LL)mat[i][k] * d % mod;
						if(mat[j][k] < 0)
							mat[j][k] += mod;
					}
				}
		}
		for(int i = 0; i <= n; ++i)
			printf("%d %d\n", mat[i][n + 1], mat[i][n + 2]);
	}
	return 0;
}
