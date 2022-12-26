/*
 * 单调栈扫一遍
 */
#include <cstdio>
int n, q[50001], tail, ans;
int main()
{
	int t, x;
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%d", &t, &x);
		while(tail && q[tail] > x) --tail, ++ans;
		if(x != q[tail]) q[++tail] = x;
	}
	printf("%d\n", ans + tail);
	return 0;
}
