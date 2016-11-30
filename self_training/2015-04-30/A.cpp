#include <cstdio>
#include <algorithm>
using namespace std;
const int maxt = 100;
int a, b, c, tot, ans[maxt];
int main()
{
	while(scanf("%d%d%d", &a, &b, &c) == 3)
	{
		tot = 0;
		for(int s = 0; s < maxt; ++s)
		{
			int cnt = 0;
			long long x = b;
			for(int k = 0; k < a; ++k)
				x *= s;
			x += c;
			if(x <= 0 || x >= (long long)1e9)
				continue;
			long long y = x;
			while(x > 0)
			{
				cnt += x % 10;
				x /= 10;
			}
			if(s == cnt)
				ans[tot++] = y;
		}
		printf("%d\n", tot);
		for(int i = 0; i < tot; ++i)
			printf("%d%c", ans[i], " \n"[i == tot - 1]);
	}
	return 0;
}
