#include <cstdio>
const int maxn = 100001;
int n, a[maxn], top, stack[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", &a[i]);
	top = -1;
	for(int i = n - 1; i >= 0; --i)
	{
		stack[++top] = a[i];
		while(top > 0 && stack[top] == stack[top - 1])
			++stack[--top];
	}
	printf("%d\n", stack[0] - top);
	return 0;
}
