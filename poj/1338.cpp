#include <cstdio>
const int maxn = 1500, maxf = 3, fact[] = {2, 3, 5};
int n, pos[3], ans[maxn];
int main()
{
	ans[0] = 1;
	for(int i = 1; i < maxn; ++i)
	{
		ans[i] = ans[pos[0]] * fact[0];
		for(int j = 1; j < maxf; ++j)
			if(ans[i] > ans[pos[j]] * fact[j])
				ans[i] = ans[pos[j]] * fact[j];
		for(int j = 0; j < maxf; ++j)
			if(ans[i] == ans[pos[j]] * fact[j])
				++pos[j];
	}
	while(scanf("%d", &n) != EOF && n)
		printf("%d\n", ans[n - 1]);
	return 0;
}