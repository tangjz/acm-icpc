/*
 * 最长上升序列.. 呵呵.. 
 */
#include <cstdio>
const int maxm = 100001;
int n, m, x[maxm], y[maxm], t[maxm], f[maxm], ans;
inline int abs(int a) { return a < 0 ? -a : a; }
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d", t + i, x + i, y + i);
	for(int i = 1; i <= m; ++i)
	{
		f[i] = 1;
		for(int j = 1; j < i; ++j)
			if(f[i] < f[j] + 1 && abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j]) f[i] = f[j] + 1;
		if(ans < f[i]) ans = f[i];
	}
	printf("%d\n", ans);
	return 0;
}
