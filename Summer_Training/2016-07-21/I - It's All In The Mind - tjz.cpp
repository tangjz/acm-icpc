#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 110;
int t, n, m, a[maxn], c, s;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &n, &m);
		memset(a + 1, -1, n * sizeof(int));
		while(m--)
		{
			int x, v;
			scanf("%d%d", &x, &v);
			a[x] = v;
		}
		s = a[n + 1] = 0;
		for(int i = n; i > 2; --i)
		{
			if(a[i] == -1)
				a[i] = a[i + 1];
			s += a[i];
		}
		c = 0;
		a[0] = 100;
		for(int i = 1; i <= 2; ++i)
		{
			if(a[i] == -1)
				a[i] = a[i - 1];
			c += a[i];
			s += a[i];
		}
		int r = __gcd(c, s);
		printf("%d/%d\n", c / r, s / r);
	}
	return 0;
}
