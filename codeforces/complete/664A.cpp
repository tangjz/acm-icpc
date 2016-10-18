#include <stdio.h>
#include <cstring>
const int maxn = 102;
char s[maxn], t[maxn];
int main()
{
	scanf("%s%s", s, t);
	puts(strcmp(s, t) ? "1" : s);
	return 0;
}
