#include <cstdio>
#include <cstring>
const int maxn = 1010;
int len, f[maxn];
char s[maxn];
int main()
{
	while(gets(s))
	{
		len = strlen(s);
		for(int i = 1, j = 0; i < len; ++i)
		{
			while(j > 0 && s[i] != s[j])
				j = f[j];
			if(s[i] == s[j])
				j = j + 1;
			f[i + 1] = j;
		}
		if(f[len] > 0 && len % (len - f[len]) == 0)
			printf("%d\n", len - f[len]);
		else
			printf("%d\n", len);
	}
	return 0;
}
