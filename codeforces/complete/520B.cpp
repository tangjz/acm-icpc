#include <stdio.h>
const int maxn = 10001;
int n, m, ans;
int main()
{
	scanf("%d%d", &n, &m);
	for( ; n < m; m >>= 1, ++ans)
		if(m & 1)
		{
			++m;
			++ans;
		}
	ans += n - m;
	printf("%d\n", ans);
	return 0;
}
