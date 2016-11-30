#include <vector>
#include <bitset>
#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001;
int sz[2], seq[2][maxn], cur, nxt = 1;
bitset<maxn> msk[2];
int main()
{
	{ // init
		int n, x, r = 0;
		scanf("%d", &n);
		for(int i = 0; i < n; ++i)
		{
			scanf("%d", &x);
			if(msk[cur].test(x))
				continue;
			seq[cur][sz[cur]++] = x;
			msk[cur].set(x);
			r = __gcd(r, x);
		}
		sort(seq[cur], seq[cur] + sz[cur]);
		if(r > 1)
		{
			msk[cur].reset();
			for(int i = 0; i < sz[cur]; ++i)
				msk[cur].set(seq[cur][i] /= r);
		}
	}
	int stp = 0;
	while(sz[cur] > 0)
	{
		if(stp > 0 && seq[cur][0] == 1)
		{
			stp += seq[cur][sz[cur] - 1];
			break;
		}
		bool flag = 0;
		for(int i = 1; i < sz[cur]; ++i)
			if(seq[cur][i] - seq[cur][i - 1] == 1)
			{
				flag = 1;
				break;
			}
		if(flag)
		{
			stp += seq[cur][sz[cur] - 1] - seq[cur][0] + 1;
			break;
		}
		int r = 0;
		sz[nxt] = 0;
		msk[nxt].reset();
		if((sz[cur] << 5) < seq[cur][sz[cur] - 1])
		{
			for(int i = 0; i < sz[cur]; ++i)
				for(int j = i + 1; j < sz[cur]; ++j)
				{
					int diff = seq[cur][j] - seq[cur][i];
					if(msk[nxt].test(diff))
						continue;
					seq[nxt][sz[nxt]++] = diff;
					msk[nxt].set(diff);
					r = __gcd(r, diff);
				}
			sort(seq[nxt], seq[nxt] + sz[nxt]);
		}
		else
		{
			for(int i = 0; i < sz[cur]; ++i)
				msk[nxt] |= msk[cur] >> seq[cur][i];
			msk[nxt].reset(0);
			for(int i = 1, lim = seq[cur][sz[cur] - 1] - seq[cur][0]; i <= lim; ++i)
				if(msk[nxt].test(i))
				{
					seq[nxt][sz[nxt]++] = i;
					r = __gcd(r, i);
				}
		}
		if(r > 1)
		{
			msk[nxt].reset();
			for(int i = 0; i < sz[nxt]; ++i)
				msk[nxt].set(seq[nxt][i] /= r);
		}
		cur ^= 1;
		nxt ^= 1;
		++stp;
	}
	printf("%d\n", stp);
	return 0;
}
