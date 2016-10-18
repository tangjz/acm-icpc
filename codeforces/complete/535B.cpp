#include <stdio.h>
#include <algorithm>
const int maxn = 1000000000, maxs = 1 << 10;
int tot, seq[maxs];
void dfs(int val)
{
	seq[tot++] = val;
	if(val <= (maxn - 4) / 10)
		dfs(val * 10 + 4);
	if(val <= (maxn - 7) / 10)
		dfs(val * 10 + 7);
}
int main()
{
	dfs(0);
	std::sort(seq, seq + tot);
	int n;
	scanf("%d", &n);
	printf("%d\n", std::lower_bound(seq, seq + tot, n) - seq);
	return 0;
}
