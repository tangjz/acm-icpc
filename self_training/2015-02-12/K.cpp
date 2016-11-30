#include <cstdio>
const int maxm = 1e5;
int n, m, a[maxm], b[maxm], aque[maxm + 1], bque[maxm + 1], ans[maxm];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		++a[x];
	}
	for(int i = 0, x; i < n; ++i)
	{
		scanf("%d", &x);
		++b[x];
	}
	for(int i = m - 1; i >= 0; --i)
	{
		while(b[m - i - 1])
		{
			bque[++bque[0]] = m - i - 1;
			--b[m - i - 1];
		}
		while(a[i])
		{
			if(bque[0])
				++ans[i + bque[bque[0]--]];
			else
				aque[++aque[0]] = i;
			--a[i];
		}
	}
	for(int i = 1; i <= aque[0]; ++i)
		++ans[aque[i] + bque[bque[0]--] - m];
	for(int i = m - 1; i >= 0; --i)
		while(ans[i]--)
			printf("%d ", i);
	putchar('\n');
	return 0;
}
