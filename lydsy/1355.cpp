#include <cstdio>
const int maxn = 1000001;
int n, f[maxn];
char s[maxn];
int main()
{
	scanf("%d%s", &n, s);
	for(int i = 1; i < n; ++i)
	{
		int j = f[i];
		while(j && s[i] != s[j])
			j = f[j];
		if(s[i] == s[j])
			f[i + 1] = ++j;
	}
	printf("%d\n", n - f[n]);
	return 0;
}
