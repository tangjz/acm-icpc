#include <cstdio>
int n, x, d[101], cnt, ans[5];
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &x);
		++d[x];
	}
	for(int i = 1; i < 10; ++i)
		if(d[i])
		{
			ans[cnt++] = i;
			break;
		}
	for(int i = 1; i < 10; ++i)
		if(d[i * 10])
		{
			ans[cnt++] = i * 10;
			break;
		}
	if(!cnt)
		for(int i = 11; i < 100; ++i)
			if(d[i])
			{
				ans[cnt++] = i;
				break;
			}
	if(d[0])
		ans[cnt++] = 0;
	if(d[100])
		ans[cnt++] = 100;
	printf("%d\n", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d%c", ans[i], " \n"[i == cnt - 1]);
	return 0;
}
