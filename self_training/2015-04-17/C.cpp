#include <cstdio>
const int maxn = 20;
int n, m, gray[1 << maxn];
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 0; i < 1 << maxn; ++i)
		gray[i] = i ^ (i >> 1);
	for(int i = 0; i < 1 << n; ++i)
		for(int j = 0; j < 1 << m; ++j)
			printf("%d%c", (gray[i] << m) + gray[j], " \n"[j == (1 << m) - 1]);
	return 0;
}
