#include <cstdio>
int sum;
char str[256];
int main()
{
	while(gets(str) && !(str[0] == '#' && str[1] == '\0'))
	{
		sum = 0;
		for(int i = 0; str[i]; ++i)
			if(str[i] >= 'A' && str[i] <= 'Z')
				sum += (i + 1) * (str[i] - 'A' + 1);
		printf("%d\n", sum);
	}
	return 0;
}