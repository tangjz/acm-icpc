#include <cstdio>
#include <algorithm>
using namespace std;
const int INF = 1000000001l;
int t, n, a[100001], b[100001];
long long ans;
int main()
{
	int i, j;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; ++i)
		{
			scanf("%d", &a[i]);
			if(a[i] == 1) a[i] = INF;
			if(a[i] == 2) a[i] = 4;
		}
		sort(a, a + n);
		for(i = 0; i < n; ++i)
		{
			scanf("%d", &b[i]);
			if(b[i] == 1) b[i] = INF;
			if(b[i] == 2) b[i] = 4;
		}
		sort(b, b + n);
		for(ans = i = j = 0; i < n; ++i)
		{
			while(a[i] >= b[j] && j < n) ++j;
			ans += n - j;
		}
		printf("%.10lf\n", (double)ans / n);
	}
	return 0;
}
