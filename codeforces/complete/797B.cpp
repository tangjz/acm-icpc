#include <cstdio>
#include <algorithm>
const int maxn = 100001;
int n, m, a[maxn], tp, ans;
int main()
{
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", a + m);
		if(a[m] & 1)
			++m;
		else if(a[m] > 0)
			tp += a[m];
	}
	std::sort(a, a + m);
	ans = (int)-2e9;
	for(int i = m - 1; i >= 0; --i)
		if(((tp += a[i]) & 1) && ans < tp)
			ans = tp;
	printf("%d\n", ans);
	return 0;
}
