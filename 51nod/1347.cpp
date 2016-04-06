#include <cstdio>
#include <cstring>
int len;
bool flag;
char str[1000010];
int main()
{
	while(scanf("%s", str) == 1)
	{
		len = strlen(str);
		flag = len & 1;
		for(int i = 0; i < len >> 1 && !flag; ++i)
			flag |= str[i] != str[i + (len >> 1)];
		puts(flag ? "NO" : "YES");
	}
	return 0;
}
