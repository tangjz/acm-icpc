#include <cstdio>
#include <cstring>
const int maxn = 10000086;
int n, p[maxn], f[maxn];
long long ans;
char s[maxn];
int min(int x, int y)
{
	return x < y ? x : y;
}
int main()
{
	scanf("%s", s);
	n = strlen(s);
	s[n * 2 + 2] = '\0';
	for(int i = n; i; --i)
	{
		s[i * 2 + 1] = '#';
		s[i * 2] = s[i - 1];
	}
	s[1] = '#';
	s[0] = '@';
	for(int i = 1, mx = 0, id; s[i]; ++i)
	{
		p[i] = mx > i ? min(p[id * 2 - i], mx - i) : 1;
		while(s[i + p[i]] == s[i - p[i]])
			++p[i];
		if(mx < i + p[i])
		{
			mx = i + p[i];
			id = i;
		}
	}
	for(int i = 1; i <= n; ++i)
	{
		if(p[i + 1] == i + 1)
			f[i] = f[i >> 1] + 1;
		ans += f[i];
	}
	printf("%lld\n", ans);
	return 0;
}
