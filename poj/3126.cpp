#include <cstdio>
#include <cstring>
const int maxx = 10001;
int t, a, b, tot, prime[maxx], l, r, que[maxx], step[maxx], ans;
bool vis[maxx], used[maxx];
int main()
{
	for(int i = 2; i < maxx; ++i)
	{
		if(!vis[i])
			prime[tot++] = i;
		for(int j = 0; j < tot && i * prime[j] < maxx; ++j)
		{
			vis[i * prime[j]] = 1;
			if(i % prime[j] == 0)
				break;
		}
	}
	scanf("%d", &t);
	while(t--)
	{
		l = r = ans = 0;
		scanf("%d%d", &a, &b);
		if(a == b)
		{
			puts("0");
			continue;
		}
		memset(used, 0, sizeof used);
		que[r++] = a;
		used[a] = 1;
		while(l < r)
		{
			int now = que[l];
			int digit[4] = {now / 1000, now / 100 % 10, now / 10 % 10, now % 10};
			for(int i = 0; i < 4; ++i)
				for(int j = 0; j <= 9; ++j)
				{
					if(!i && !j || i == 3 && !(j & 1) || digit[i] == j)
						continue;
					int tmp = digit[i];
					digit[i] = j;
					int res = ((digit[0] * 10 + digit[1]) * 10 + digit[2]) * 10 + digit[3];
					if(!vis[res] && !used[res])
					{
						step[r] = step[l] + 1;
						used[res] = 1;
						if(b == res)
							goto finished;
						que[r++] = res;
					}
					digit[i] = tmp;
				}
			++l;
		}
	finished:
		if(used[b])
			printf("%d\n", step[r]);
		else
			puts("Impossible");
	}
	return 0;
}