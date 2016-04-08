#include <cstdio>
#include <cstring>
const int maxn = 21;
int n, q, seq[maxn];
long long val, fact[maxn];
bool vis[maxn];
int main()
{
	scanf("%d%d", &n, &q);
	fact[0] = 1;
	for(int i = 1; i < n; ++i)
		fact[i] = fact[i - 1] * i;
	while(q--)
	{
		char op[2];
		scanf("%s", op);
		memset(vis, 0, sizeof vis);
		if(op[0] == 'P')
		{
			scanf("%lld", &val);
			--val;
			for(int i = 1; i <= n; ++i)
			{
				int cnt = val / fact[n - i];
				for(int j = 1; j <= n; ++j)
					if(!vis[j] && !(cnt--))
					{
						seq[i] = j;
						break;
					}
				vis[seq[i]] = 1;
				val %= fact[n - i];
			}
			for(int i = 1; i <= n; ++i)
				printf("%d%c", seq[i], " \n"[i == n]);
		}
		else
		{
			for(int i = 1; i <= n; ++i)
				scanf("%d", seq + i);
			val = 0;
			for(int i = 1; i <= n; ++i)
			{
				int cnt = 0;
				for(int j = 1; j < seq[i]; ++j)
					if(!vis[j])
						++cnt;
				val += cnt * fact[n - i];
				vis[seq[i]] = 1;
			}
			++val;
			printf("%lld\n", val);
		}
	}
	return 0;
}
