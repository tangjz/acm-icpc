#include <cstdio>
const int maxn = 100001;
const char* goa = "luvletter";
int t, ans;
char str[maxn];
int main()
{
	scanf("%d\n", &t);
	while(t--)
	{
		ans = 0;
		gets(str);
		for(int i = 0, j = 0; str[i]; ++i)
			if(str[i] == goa[j] && goa[++j] == '\0')
			{
				++ans;
				j = 0;
			}
		printf("%d\n", ans);
	}
	return 0;
}
