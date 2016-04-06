#include <cstdio>
int ch, f[1000010], top, ans, cnt = 1;
int main()
{
	while((ch = getchar()) != EOF && ch >= '(')
	{
		if(ch == '(')
		{
			++f[top];
			f[++top] = 0;
		}
		else if(top)
		{
			f[top - 1] += f[top] + 1;
			--top;
		}
		else
			f[top] = 0;
		if(ans < f[top])
		{
			ans = f[top];
			cnt = 1;
		}
		else if(ans && ans == f[top])
			++cnt;
	}
	printf("%d %d\n", ans, cnt);
	return 0;
}
