#include <cstdio>
const int maxn = 80002;
int n, seq[maxn], stack[maxn], top;
long long ans;
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", seq + i);
	seq[n + 1] = ~0u >> 1;
	stack[top++] = n + 1;
	for(int i = n; i >= 1; --i)
	{
		while(top && seq[stack[top - 1]] < seq[i])
			--top;
		ans += stack[top - 1] - i - 1;
		stack[top++] = i;
	}
	printf("%lld\n", ans);
	return 0;
}
