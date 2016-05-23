#include <stdio.h>
const int maxn = 1001;
int t, n;
char str[maxn];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		n = 0;
		scanf("%s", str);
		for(int i = 0; str[i]; ++i)
			n = (n + str[i] - '0') % 3;
		puts(n ? "A" : "B");
	}
	return 0;
}
