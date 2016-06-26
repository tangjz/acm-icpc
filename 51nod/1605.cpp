#include <stdio.h>
const int maxn = 101;
int t, n, m, x, ans;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		ans = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
			{
				scanf("%d", &x);
				ans ^= x;
			}
		puts(ans ? "yadang" : "xiawa");
	}
	return 0;
}
