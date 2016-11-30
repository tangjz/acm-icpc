#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 1000001, maxl = 7, Low = 100, High = 1000;
int tot, a[maxn], t, n;
bool palindrome(int x)
{
	int len;
	static char str[maxl], buf[maxl];
	len = sprintf(str, "%d", x);
	strcpy(buf, str);
	std::reverse(buf, buf + len);
	return !strcmp(str, buf);
}
int main()
{
	for(int i = Low; i < High; ++i)
		for(int j = Low; j < High; ++j)
			if(palindrome(i * j))
				a[tot++] = i * j;
	std::sort(a, a + tot);
	tot = std::unique(a, a + tot) - a;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		printf("%d\n", *(std::upper_bound(a, a + tot, n - 1) - 1));
	}
	return 0;
}
