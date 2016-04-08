/*
 * 喜闻乐见的简单模拟... 
 */
#include <cstdio>
typedef long long LL;
const int maxn = 10000001;
int n, A, B, C, a[maxn];
double ans;
int main()
{
	scanf("%d%d%d%d%d", &n, &A, &B, &C, &a[0]);
	for(int i = 1; i < n; ++i)
		a[i] = ((LL)a[i - 1] * A + B) % 100000001;
	for(int i = 0; i < n; ++i)
		a[i] = a[i] % C + 1;
	a[n] = a[0];
	for(int i = 0; i < n; ++i)
		ans += 1.0 / (a[i] < a[i + 1] ? a[i + 1] : a[i]);
	printf("%.3lf\n", ans);
	return 0;
}
