#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100001, maxd = 17, mod = 1000000007;
int n, a[maxn], szA, szO, ans;
pair<int, int> stkA[maxn], stkO[maxn];
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for(int i = 1; i <= n; ++i)
	{
		{ // And
			stkA[szA++] = make_pair(~0u >> 1, i);
			for(int j = 0; j < szA; ++j)
				stkA[j].first &= a[i];
			int tp = 0;
			for(int j = 0; j < szA; ++j)
				if(!tp || stkA[tp - 1].first != stkA[j].first)
					stkA[tp++] = stkA[j];
			szA = tp;
		}
		{ // Or
			stkO[szO++] = make_pair(0, i);
			for(int j = 0; j < szO; ++j)
				stkO[j].first |= a[i];
			int tp = 0;
			for(int j = 0; j < szO; ++j)
				if(!tp || stkO[tp - 1].first != stkO[j].first)
					stkO[tp++] = stkO[j];
			szO = tp;
		}
		for(int p = szA - 1, q = szO - 1, L, R = i + 1; p >= 0 && q >= 0; )
		{
			L = max(stkA[p].second, stkO[q].second);
			ans = (ans + (LL)stkA[p].first * stkO[q].first % mod * (R - L)) % mod;
			if(L == stkA[p].second)
				--p;
			if(L == stkO[q].second)
				--q;
			R = L;
		}
	}
	printf("%d\n", ans);
	return 0;
}
