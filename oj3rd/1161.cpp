#include <cstdio>
int cnt;
char s[1010], t[1010];
int main()
{
	while(scanf("%s%s", s, t) == 2)
	{
		cnt = 0;
		for(int i = 0, j = 0; s[i]; ++i)
		{
			if(s[i] == t[j])
				++j;
			else
				j = s[i] == t[0];
			if(!t[j])
			{
				++cnt;
				j = 0;
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
