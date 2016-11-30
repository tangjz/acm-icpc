#include <stdio.h>
#include <cstring>
const int maxn = 10001;
int len, ans;
char str[maxn];
int main()
{
	scanf("%s", str);
	len = strlen(str);
	ans = 10 * (len - 1);
	for(int i = 1; i <= 9; ++i)
	{
		int j;
		for(j = 0; j < len; ++j)
			if(str[j] != '0' + i)
				break;
		if(j == len || str[j] > '0' + i)
			++ans;
	}
	printf("%d\n", ans);
	return 0;
}
