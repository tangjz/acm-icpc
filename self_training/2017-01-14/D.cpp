#include <stdio.h>
#include <algorithm>
typedef long long LL;
const int maxn = 362881, maxd = 26, maxs = 9, score[maxs] = {0, 0, 1, 1, 2, 3, 5, 11, 11};
int t, n, perm[maxs], sz[maxs];
char str[maxs + 2];
LL seq[maxs][maxn];
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		for(int i = 0; i < 3; ++i)
			scanf("%s", str + i * 3);
		for(int i = 0; i < maxs; ++i)
		{
			perm[i] = i;
			sz[i] = 0;
		}
		do
		{
			LL Hash = 0;
			for(int i = 0; i < maxs; ++i)
			{
				static int px, py, cx, cy;
				cx = perm[i] / 3;
				cy = perm[i] % 3;
				if(i && std::max(std::abs(px - cx), std::abs(py - cy)) > 1)
					break;
				Hash = Hash * maxd + (str[perm[i]] - 'A');
				seq[i][sz[i]++] = Hash;
				px = cx;
				py = cy;
			}
		} while(std::next_permutation(perm, perm + maxs));
		for(int i = 0; i < maxs; ++i)
		{
			std::sort(seq[i], seq[i] + sz[i]);
			sz[i] = std::unique(seq[i], seq[i] + sz[i]) - seq[i];
		}
		scanf("%d", &n);
		printf("Case #%d:\n", Case);
		while(n--)
		{
			int len;
			LL Hash = 0;
			scanf("%s", str);
			for(len = 0; str[len]; ++len)
				Hash = Hash * maxd + (str[len] - 'A');
			--len;
			int idx = std::lower_bound(seq[len], seq[len] + sz[len], Hash) - seq[len];
			printf("%d\n", seq[len][idx] == Hash ? score[len] : 0);
		}
	}
	return 0;
}
