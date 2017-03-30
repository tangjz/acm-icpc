//#include <map>
//#include <set>
#include <cstdio>
typedef long long LL;
const int maxm = 30, maxs = 31623;
const int sg[maxm | 1] = {0, 1, 2, 1, 4, 3, 2, 1, 5, 6, 2, 1, 8, 7, 5, 9, 8, 7, 3, 4, 7, 4, 2, 1, 10, 9, 3, 6, 11, 12};
int n, sqn, mx, f[maxm | 1];
bool vis[maxs];
/*std::map<int, int> Hash;
int SG(int mask)
{
	if(Hash.count(mask))
		return Hash[mask];
	std::set<int> mex;
	for(int i = 0; i < maxm; ++i)
	{
		if(!((mask >> i) & 1))
			continue;
		int tp = mask;
		for(int j = i; j < maxm; j += i + 1)
			if((mask >> j) & 1)
				tp ^= 1 << j;
		mex.insert(SG(tp));
	}
	int ret = 0;
	for( ; mex.count(ret); ++ret);
	return Hash[mask] = ret;
}*/
int main()
{
	/*sg[0] = Hash[0] = 0;
	for(int i = 1; i < maxm; ++i)
		printf("%d, ", sg[i] = SG((1 << i) - 1));*/
	scanf("%d", &n);
	for(sqn = 1; sqn * sqn <= n; ++sqn);
	--sqn;
	f[1] = n - sqn + 1;
	mx = 1;
	for(int i = 2; i <= sqn; ++i)
	{
		if(vis[i])
			continue;
		int cnt = 0, cur = 1, lim = n / i;
		for( ; cur <= lim; ++cnt)
		{
			cur *= i;
			if(cur <= sqn)
				vis[cur] = 1;
			else
				--f[1];
		}
		++f[cnt];
		if(mx < cnt)
			mx = cnt;
	}
	int SG = 0;
	for(int i = 1; i <= mx; ++i)
		if(f[i] & 1)
			SG ^= sg[i];
	puts(SG ? "Vasya" : "Petya");
	return 0;
}
