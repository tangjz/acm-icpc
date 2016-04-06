#include <cstdio>
int n, f[31];
int cnt(int x)
{
	if(f[x]) return f[x];
	if(x <= 1) return 0;
	return f[x] = cnt(x - 1) + cnt(x - 2) + 1;
}
int main()
{
	while(scanf("%d", &n) != EOF) printf("%d\n", cnt(n));
	return 0;
}
