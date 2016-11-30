#include <stdio.h>
const int maxs = 11;
char str[maxs];
int dt;
int main()
{
	scanf("%s%d", str, &dt);
	for(int i = 0; str[i]; ++i)
		str[i] = (str[i] - '0' + dt) % 10 + '0';
	puts(str);
	return 0;
}
