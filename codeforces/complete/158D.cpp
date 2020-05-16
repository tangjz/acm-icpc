#include <cstdio>
const int maxn = 20001, INF = 0x3f3f3f3f;
int n, t[maxn], ans;
int main()
{
	while(scanf("%d", &n) == 1)
	{
		ans = -INF;
		for(int i = 0; i < n; ++i)
			scanf("%d", t + i);
		for(int i = 1; i * i <= n; ++i)
			if(n % i == 0)
			{
				if(n / i >= 3)
					for(int j = 0; j < i; ++j)
					{
						int tmp = 0;
						for(int k = j; k < n; k += i)
							tmp += t[k];
						if(ans < tmp)
							ans = tmp;
					}
				if(i != n / i && i >= 3)
					for(int j = 0; j < n / i; ++j)
					{
						int tmp = 0;
						for(int k = j; k < n; k += n / i)
							tmp += t[k];
						if(ans < tmp)
							ans = tmp;
					}
			}
		printf("%d\n", ans);
	}
	return 0;
}
