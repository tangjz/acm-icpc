#include <stdio.h>
#include <algorithm>
const int maxn = 101, maxd = 30;
int n, a[maxn], b[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int d = maxd - 1; d >= 0; --d)
	{
		for(int i = 0; i < n; ++i)
			b[i] = a[i] >> d;
		std::sort(b, b + n);
		bool flag = 1;
		for(int i = 0, j = 0; i < n; i = j)
		{
			for( ; j < n && b[i] == b[j]; ++j);
			if(j - i > (n >> 1))
			{
				flag = 0;
				break;
			}
		}
		if(flag)
		{
			printf("%d\n", d);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
