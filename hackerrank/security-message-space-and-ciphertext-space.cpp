#include <stdio.h>
const int maxs = 11;
char str[maxs];
int main()
{
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
		str[i] = (str[i] - '0' + 1) % 10 + '0';
	puts(str);
	return 0;
}
