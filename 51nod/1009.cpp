#include <stdio.h>
#include <cstring>
const int maxs = 10;
typedef long long LL;
int n, pw10, ans;
char s[maxs];
int main()
{
	scanf("%d", &n);
	sprintf(s, "%d", n + 1);
	n = strlen(s);
	pw10 = 1;
	for(int i = 1; i < n; ++i)
		pw10 *= 10;
	for(int i = 0, c = 0; i < n; ++i)
	{
		if(s[i] > '0')
		{
			int all = pw10 * (s[i] - '0');
			ans += all * c;
			if(i + 1 < n)
				ans += all / 10 * (n - i - 1);
			if(s[i] > '1')
				ans += pw10;
		}
		pw10 /= 10;
		c += s[i] == '1';
	}
	printf("%d\n", ans);
	return 0;
}
