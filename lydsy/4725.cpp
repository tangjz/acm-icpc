#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 101, maxv = (int)1e9 + 1, maxs = 1449;
int n, r[maxn], tot, que[maxs];
LL f[maxn];
map<int, pair<int, int> > Hash;
int main()
{
	f[1] = r[1] = 1;
	f[2] = r[2] = 2;
	Hash[f[2] - f[1]] = make_pair(2, 1);
	for(n = 3; ; ++n)
	{
		f[n] = n & 1 ? f[n - 1] << 1 : f[n - 1] + r[n - 1];
		for(int i = 1; i < n; ++i)
		{
			LL diff = f[n] - f[n - i];
			if(diff >= maxv)
				break;
			// if(!Hash.count(diff))
			Hash[diff] = make_pair(n, n - i);
		}
		for(r[n] = r[n - 1]; Hash.count(r[n]); ++r[n]);
		// printf("%d : %lld %d\n", n, f[n], r[n]);
		if(f[n] - f[n - 1] >= maxv)
			break; // now, n is odd
	}
	for(map<int, pair<int, int> >::iterator it = Hash.begin(); it != Hash.end(); ++it)
		que[tot++] = it -> first;
	int q, x;
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d", &x);
		if(Hash.count(x))
		{
			pair<int, int> res = Hash[x];
			printf("%d %d\n", res.first, res.second);
		}
		else // even - odd
		{
			int rem = x - (upper_bound(que, que + tot, x) - que) - 1;
			printf("%d %d\n", n + (rem << 1) + 1, n + (rem << 1));
		}
	}
	return 0;
}
