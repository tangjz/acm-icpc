#include <stdio.h>
#include <cstring>
typedef long long LL;
const int maxn = 10010;
int t, x, c, mod, seq[maxn], pos[maxn];
LL n;
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		int beg, end;
		scanf("%d%I64d%d%d", &x, &n, &mod, &c);
		memset(pos, 0, mod * sizeof(int));
		seq[1] = x %= mod;
		pos[seq[1]] = 1;
		for(int i = 2; i <= mod; ++i)
		{
			seq[i] = (seq[i - 1] * 10 + x) % mod;
			if(!pos[seq[i]])
				pos[seq[i]] = i;
			else
			{
				beg = pos[seq[i]];
				end = i;
				break;
			}
		}
		printf("Case #%d:\n%s\n", Case, seq[n < beg ? n : (n - beg) % (end - beg) + beg] == c ? "Yes" : "No");
	}
	return 0;
}
