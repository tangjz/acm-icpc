#include <stdio.h>
const int maxn = 100001, maxd = 36;
int lim, sum;
char str[maxn];
int main()
{
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
	{
		str[i] = str[i] >= '0' && str[i] <= '9' ? str[i] - '0' : str[i] - 'A' + 10;
		if(lim < str[i])
			lim = str[i];
		sum += str[i];
	}
	for(int i = lim; i < maxd; ++i)
		if(sum % i == 0)
		{
			printf("%d\n", i + 1);
			return 0;
		}
	puts("No Solution");
	return 0;
}
