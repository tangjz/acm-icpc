#include <cstdio>
#include <cstring>
const int maxn = 4001, mod = 960991;
struct Node
{
	int cnt, nxt;
	long long num;
} e[maxn * maxn];
int n, tot, pre[mod];
long long a[maxn][4], ans;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		tot = ans = 0;
		memset(pre, 0, sizeof pre);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < 4; ++j)
				scanf("%lld", &a[i][j]);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				long long tmp = a[i][0] + a[j][1];
				int it, hh = tmp % mod;
				if(hh < 0)
					hh += mod;
				for(it = pre[hh]; it; it = e[it].nxt)
					if(e[it].num == tmp)
						break;
				if(it)
					++e[it].cnt;
				else
				{
					e[++tot] = {1, pre[hh], tmp};
					pre[hh] = tot;
				}
			}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
			{
				long long tmp = -a[i][2] - a[j][3];
				int it, hh = tmp % mod;
				if(hh < 0)
					hh += mod;
				for(it = pre[hh]; it; it = e[it].nxt)
					if(e[it].num == tmp)
						break;
				ans += e[it].cnt;
			}
		printf("%lld\n", ans);
	}
	return 0;
}
