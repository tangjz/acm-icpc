#include <stdio.h>
const int maxn = 100001, maxd = 11, mod = 1000000001;
int n, len, seq[maxn], f[2][1 << maxd | 1], pre = 1, cur, ans;
bool vis[maxn];
int main()
{
	scanf("%d", &n);
	ans = 1;
	for(int i = 1; i <= n; ++i)
	{
		if(vis[i])
			continue;
		len = 1;
		seq[0] = i;
		vis[i] = 1;
		f[cur][0] = f[cur][1] = 1;
		while(len)
		{
			int plen = len;
			pre ^= 1;
			cur ^= 1;
			for(int i = 0; i < len; ++i)
				if(seq[i] << 1 <= n)
					seq[i] <<= 1;
				else
				{
					len = i;
					break;
				}
			if(len && seq[len - 1] + (seq[len - 1] >> 1) <= n)
			{
				seq[len] = seq[len - 1] + (seq[len - 1] >> 1);
				++len;
			}
			for(int i = 0; i < len; ++i)
				vis[seq[i]] = 1;
			for(int i = 0; i < 1 << len; ++i)
				f[cur][i] = 0;
			for(int i = 0; i < 1 << plen; ++i)
			{
				int msk = ~(i << 1 | i) & ((1 << len) - 1);
				for(int j = msk; ; j = (j - 1) & msk)
				{
					if((f[cur][j] += f[pre][i]) >= mod)
						f[cur][j] -= mod;
					if(!j)
						break;
				}
			}
		}
		ans = (long long)ans * f[cur][0] % mod;
	}
	printf("%d\n", ans);
	return 0;
}
