#include <cstdio>
#include <cstring>
#include <cctype>

int cnt;
char s[100009];
const char t[]="doge";

int main()
{
	while (gets(s))
	{
		for (char *p=s;*p;++p) *p=tolower(*p);
		for (char *p=s;*p;)
		{
			if (strstr(p,t))
			{
				++cnt;
				p=strstr(p,t)+1;
			}
			else break;
		}
	}
	printf("%d\n",cnt);
    return 0;
}
