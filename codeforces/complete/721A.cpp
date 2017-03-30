#include <cstdio>
const int maxn = 101;
int n, cnt, a[maxn];
char str[maxn];
int main()
{
	scanf("%d%s", &n, str + 1);
	str[0] = 'W';
	for(int i = 0; i <= n; ++i)
	{
		for( ; i <= n && str[i] == 'W'; ++i);
		if(str[i] == 'B')
			for(++cnt; i <= n && str[i] == 'B'; ++i, ++a[cnt]);
	}
	printf("%d\n", cnt);
	for(int i = 1; i <= cnt; ++i)
		printf("%d%c", a[i], " \n"[i == cnt]);
	return 0;
}
