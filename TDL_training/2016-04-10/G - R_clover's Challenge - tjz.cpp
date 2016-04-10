#include <map>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 32768;
int t, x, ffx;
map<int, int> Hash;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		Hash.clear();
		scanf("%d%d", &x, &ffx);
		for(int k1 = 0; k1 < maxn; ++k1)
		{
			int L = x >> 15, R = x & ((1 << 15) - 1);
			for(int i = 0; i < 8; ++i)
			{
				int nL = R, nR = L ^ (R * k1 % (maxn - 1));
				L = nL, R = nR;
			}
			int fx = L << 15 | R;
			if(!Hash.count(fx))
				Hash[fx] = k1;
		}
		for(int k2 = 0; k2 < maxn; ++k2)
		{
			int nL = ffx >> 15, nR = ffx & ((1 << 15) - 1);
			for(int i = 0; i < 8; ++i)
			{
				int R = nL, L = nR ^ (R * k2 % (maxn - 1));
				nL = L, nR = R;
			}
			int fx = nL << 15 | nR;
			if(Hash.count(fx))
			{
				printf("%d %d\n", Hash[fx], k2);
				break;
			}
		}
	}
	return 0;
}
