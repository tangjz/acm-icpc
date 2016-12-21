#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 51;
int t, n, seq[maxn][maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		LL ans = 0;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
		{
			scanf("%d", seq[i] + 0);
			int mx = 1;
			for(int j = 1; j <= seq[i][0]; ++j)
			{
				scanf("%d", seq[i] + j);
				if(seq[i][mx] > seq[i][j])
					mx = j;
			}
			swap(seq[i][1], seq[i][mx]);
			ans += seq[i][1];
		}
		for(int i = 1; i <= n; ++i)
			for(int j = 2; j <= seq[i][0]; ++j)
				ans = __gcd(ans, (LL)(seq[i][j] - seq[i][1]));
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}
