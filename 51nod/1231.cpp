#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 41, maxm = 781, mod = 1000000007;
int t, n, a[maxn], iact[maxn], f[2][maxn][maxm], cur, pre = 1;
int main()
{
	iact[1] = 1;
	for(int i = 2; i < maxn; ++i)
		iact[i] = mod - (int)(mod / i * (LL)iact[mod % i] % mod);
	iact[0] = 1;
	for(int i = 1; i < maxn; ++i)
		iact[i] = (LL)iact[i - 1] * iact[i] % mod;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		int cnt = n, upp = (n * (n - 1)) >> 1;
		memset(a, 0, n * sizeof(int));
		for(int i = 0, x; i < n; ++i)
		{
			scanf("%d", &x);
			if(x >= 0)
			{
				++a[x];
				--cnt;
				upp -= x;
			}
		}
		if(upp < 0)
		{
			puts("0");
			continue;
		}
		memset(f[cur], 0, sizeof f[0]);
		f[cur][0][0] = 1;
		for(int i = 0, pc = 0, cc = 0, ps = 0, cs = 0; i < n; ++i)
		{
			pre ^= 1;
			cur ^= 1;
			memset(f[cur], 0, sizeof f[0]);
			cc += a[i];
			cs += a[i] * i;
			for(int j = 0; j <= cnt; ++j)
			{
				int low = (((j + pc) * (j + pc - 1)) >> 1) - ps;
				if(low < 0)
					low = 0;
				for(int k = low; k <= upp; ++k)
					if(f[pre][j][k])
					{
						int scr = k, lim = (((j + cc) * (j + cc - 1)) >> 1) - cs;
						for(int o = j; o <= cnt && scr <= upp; ++o)
						{
							if(scr < lim)
								break;
							// printf("(%d, %d, %d) -> (%d, %d, %d)\n", i - 1, j, k, i, o, scr);
							f[cur][o][scr] = (f[cur][o][scr] + (LL)iact[o - j] * f[pre][j][k]) % mod;
							scr += i;
							lim += o + cc;
						}
					}
			}
			pc = cc;
			ps = cs;
		}
		int ans = f[cur][cnt][upp];
		for(int i = 1; i <= cnt; ++i)
			ans = (LL)ans * i % mod;
		printf("%d\n", ans);
	}
	return 0;
}
