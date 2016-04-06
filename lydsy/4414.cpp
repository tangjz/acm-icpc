#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 300000;
int c, m, n, a[maxn << 1];
int main()
{
	scanf("%d%d%d", &c, &m, &n);
	if(n == 1)
	{
		puts("0");
		return 0;
	}
	c = (LL)c * c % m;
	n = n * 2 - 3;
	for(int i = 0, x = 8LL * c % m, y = 13LL * c % m; i < n; ++i)
	{
		a[i] = y;
		x += y;
		if(x >= m)
			x -= m;
		y += x;
		if(y >= m)
			y -= m;
	}
	sort(a, a + n);
	printf("%d\n", (unique(a, a + n) - a) % m);
	return 0;
}
