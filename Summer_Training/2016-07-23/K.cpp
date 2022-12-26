#include <cstdio>
#include <algorithm>
const int maxn = 100;
int n, a[maxn], tot, que[maxn];
char str[maxn][maxn + 1];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%s", str[i]);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i < n; ++i)
	{
		int k = -1;
		for(int j = 0; j < n; ++j)
			if(!a[j])
			{
				k = j;
				break;
			}
		if(k == -1)
			break;
		que[tot++] = k;
		for(int j = 0; j < n; ++j)
			if(str[k][j] == '1')
				--a[j];
	}
	std::sort(que, que + tot);
	printf("%d\n", tot);
	for(int i = 0; i < tot; ++i)
		printf("%d%c", que[i] + 1, " \n"[i == tot - 1]);
	return 0;
}
