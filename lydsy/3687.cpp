#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxs = 2000001;
int n, x, sum, ans;
bitset<maxs> cnt;
int main()
{
	scanf("%d", &n);
	cnt[0] = 1;
	for(int i = 0; i < n; ++i)
	{
		scanf("%d", &x);
		sum += x;
		cnt ^= cnt << x;
	}
	for(int i = 1; i <= sum; ++i)
		if(cnt[i])
			ans ^= i;
	printf("%d\n", ans);
	return 0;
}
