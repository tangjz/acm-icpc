/*
ID: tangjin2
LANG: C++
TASK: calfflac
*/
#include <cstdio>
#include <cstring>
const int maxn = 256001;
char ch[maxn], tmp[100], s[maxn];
int n, m, p[maxn], ans;
bool check(char x) { return x >= 'A' && x <= 'Z' || x >= 'a' && x <= 'z'; }
char transfrom(char x) { return x >= 'a' ? x - 'a' + 'A' : x; }
int main()
{
	freopen("calfflac.in", "r", stdin);
	freopen("calfflac.out", "w", stdout);
	int i, j, x, y;
	while(gets(tmp))
	{
		strcat(ch, tmp);
		strcat(ch, "\n");
		memset(tmp, 0, sizeof tmp);
	}
	n = strlen(ch);
	for(i = 0; i < n; ++i)
		if(check(ch[i]))
		{
			p[m] = i;
			s[m++] = transfrom(ch[i]);
		}
	for(i = 0; i < m; ++i)
	{
		for(j = 0; i - j >= 0 && i + j < m && s[i - j] == s[i + j]; ++j); --j;
		if(j * 2 + 1 > ans)
		{
			ans = j * 2 + 1;
			x = p[i - j];
			y = p[i + j];
		}
		for(j = 0; i - j >= 0 && i + j + 1 < m && s[i - j] == s[i + j + 1]; ++j); --j;
		if(j * 2 + 2 > ans)
		{
			ans = j * 2 + 2;
			x = p[i - j];
			y = p[i + j + 1];
		}
	}
	printf("%d\n", ans);
	for(i = x; i <= y; ++i) putchar(ch[i]);
	putchar('\n');
	fclose(stdin);
	fclose(stdout);
	return 0;
}
