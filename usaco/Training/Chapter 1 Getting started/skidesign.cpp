/*
ID: tangjin2
LANG: C++
TASK: skidesign
*/
#include <cstdio>
const int maxn = 1001, maxv = 101, INF = 0x3f3f3f3f;
int n, a[maxn], sum, ans = INF;
int main()
{
	freopen("skidesign.in", "r", stdin);
	freopen("skidesign.out", "w", stdout);
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	for(int i = 0; i + 17 < maxv; ++i)
	{
		sum = 0;
		for(int j = 0; j < n; ++j)
			if(a[j] < i)
				sum += (i - a[j]) * (i - a[j]);
			else if(a[j] > i + 17)
				sum += (a[j] - i - 17) * (a[j] - i - 17);
		if(ans > sum)
			ans = sum;
	}
	printf("%d\n", ans);
	return 0;
}
