#include <map>
#include <stdio.h>
using namespace std;
const int mod = 1000000007;
int t, n, m, x;
map<int, int> Hash;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		Hash.clear();
		scanf("%d%d", &n, &m);
		Hash[1] = 1;
		Hash[m] = 0;
		for(int i = 2; i <= m / i; ++i)
			if(m % i == 0)
			{
				Hash[i] = 0;
				if(i < m / i)
					Hash[m / i] = 0;
			}
		while(n--)
		{
			scanf("%d", &x);
			if(m % x)
				continue;
			int tmp = m / x, i;
			for(i = 1; i <= tmp / i; ++i)
				if(tmp % i == 0)
				{
					Hash[m / i] += Hash[tmp / i];
					if(Hash[m / i] >= mod)
						Hash[m / i] -= mod;
				}
			--i;
			if(i == tmp / i)
				--i;
			for( ; i >= 1; --i)
				if(tmp % i == 0)
				{
					Hash[i * x] += Hash[i];
					if(Hash[i * x] >= mod)
						Hash[i * x] -= mod;
				}
		}
		printf("%d\n", Hash[m]);
	}
	return 0;
}
