#include <cstdio>
char str[233333];
int main()
{
	while(scanf("%s", str) == 1)
	{
		int pos1, pos2, sum1 = 0, sum2 = 0;
		for(int i = 0; str[i]; ++i)
			if(str[i] >= 'a' && str[i] <= 'z')
			{
				pos1 = i;
				++sum1;
			}
			else if(str[i] >= 'A' && str[i] <= 'Z')
			{
				pos2 = i;
				++sum2;
			}
		if(sum1 == 1 && sum2 != 1)
			printf("%d\n", pos1 + 1);
		else if(sum1 != 1 && sum2 == 1)
			printf("%d\n", pos2 + 1);
		else
			puts("-1");
	}
	return 0;
}
