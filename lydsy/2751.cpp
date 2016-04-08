#include <queue>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxk = 100001, mod = 1000000007;
typedef long long LL;
int n, m, k, ans = 1;
pair<int, int> seq[maxk];
int mod_pow(int x, int k)
{
	int ret = 1;
	while(k)
	{
		if(k & 1)
			ret = (LL)ret * x % mod;
		x = (LL)x * x % mod;
		k >>= 1;
	}
	return ret;
}
int main()
{
	scanf("%d%d%d", &n, &m, &k);
	n = (LL)n * (n + 1) / 2 % mod;
	for(int i = 0; i < k; ++i)
		scanf("%d%d", &seq[i].first, &seq[i].second);
	sort(seq, seq + k);
	k = unique(seq, seq + k) - seq;
	for(int i = 0, j, o; i < k; i = j)
	{
		--m;
		for(j = i, o = n; j < k && seq[i].first == seq[j].first; ++j)
		{
			o -= seq[j].second;
			if(o < 0)
				o += mod;
		}
		ans = (LL)ans * o % mod;
	}
	ans = (LL)ans * mod_pow(n, m) % mod;
	printf("%d\n", ans);
	return 0;
}
