#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, a[200001], x;
void scan(int &x)
{
	static int ch, f = 0;
	while(((ch = getchar()) < '0' || ch > '9') && ch != '-');
	f = ch == '-';
	x = f ? 0 : ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + ch - '0';
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2)
	{
		for(int i = 1; i <= n; ++i)
			scan(a[i]);
		while(m--)
		{
			scan(x);
			int k = lower_bound(a + 1, a + n + 1, x) - a;
			if(k > n || x != a[k])
				puts("QWQ");
			else
				printf("%d\n", k);
		}
	}
	return 0;
}
