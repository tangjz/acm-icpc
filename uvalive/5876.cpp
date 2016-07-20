#include <cstdio>
#include <cstring>
const int maxn = 50010;
int t, n, f[maxn << 1], ans;
char tmp[maxn], str[maxn << 1];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%s%s", tmp, str);
		n = strlen(str) + 1;
		str[n] = '\0';
		strcat(str + n, tmp);
		n += strlen(str + n);
		for(int i = 1, j = 0; i < n; ++i)
		{
			for( ; j && str[i] != str[j]; j = f[j]);
			f[i + 1] = str[i] == str[j] ? ++j : 0;
		}
		ans = 0;
		for(int i = n; i > 0; i = f[i])
			++ans;
		printf("%d\n", ans);
	}
	return 0;
}
