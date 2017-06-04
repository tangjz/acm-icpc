#include <stdio.h>
#include <algorithm>
const int maxn = 50001;
int n, x[2], f[2][2], cur, pre = 1;
int main()
{
	scanf("%d%d", &n, x + cur);
	f[cur][0] = f[cur][1] = 0;
	for(int i = 1; i < n; ++i)
	{
		pre ^= 1;
		cur ^= 1;
		scanf("%d", x + cur);
		f[cur][0] = std::max(f[pre][0], f[pre][1] + x[pre] - 1);
		f[cur][1] = std::max(f[pre][0] + x[cur] - 1, f[pre][1] + std::abs(x[cur] - x[pre]));
	}
	printf("%d\n", std::max(f[cur][0], f[cur][1]));
	return 0;
}
