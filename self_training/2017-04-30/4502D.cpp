#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxs = 101;
int t;
LL n;
bool solve(LL val, int cnt)
{
	int rem = __builtin_popcountll(val);
	if(rem > cnt)
		return 0;
	int sz = 0;
	static int seq[maxs];
	for(int i = 60; i >= 0; --i)
	{
		if(!((val >> i) & 1))
			continue;
		int lim = (int)min(cnt - sz - rem + 1LL, 1LL << i), dt;
		for(dt = 0; (1 << dt) <= lim; ++dt);
		--dt;
		for(int j = 0; j < (1 << dt); ++j)
			seq[sz++] = i - dt;
		--rem;
	}
	if(sz != cnt)
		return 0;
	printf("%d ", cnt);
	for(int i = 0; i < cnt; ++i)
		printf("%d%c", seq[i], " \n"[i == cnt - 1]);
	return 1;
}
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lld", &n);
		for(int i = 1; ; ++i)
			if(solve(n * i, i))
				break;
	}
	return 0;
}
