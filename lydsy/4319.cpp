#include <cstdio>
const int maxn = 500001;
int n, sa[maxn], rk[maxn];
char s[maxn], ch;
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", sa + i);
		rk[--sa[i]] = i;
	}
	s[sa[0]] = ch = 'a';
	for(int i = 1; i < n; ++i)
	{
		if(rk[sa[i - 1] + 1] > rk[sa[i] + 1] && ++ch > 'z')
		{
			puts("-1");
			return 0;
		}
		s[sa[i]] = ch;
	}
	puts(s);
	return 0;
}
