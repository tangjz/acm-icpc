#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5010, INF = 0x3f3f3f3f;
int pos[24][4];
int t, n, seq[maxn][4][2], f[maxn][24], ans;
bool valid(int id, int mask)
{
	for(int i = 1; i < 4; ++i)
		if(seq[id][pos[mask][i]][1] < seq[id][pos[mask][i - 1]][1])
			return 0;
	return 1;
}
int cost(int id, int msk1, int msk2)
{
	int cnt = 0;
	for(int i = 0; i < 4; ++i)
		cnt += abs(seq[id][pos[msk1][i]][0] - seq[id - 1][pos[msk2][i]][0])
		+ abs(seq[id][pos[msk1][i]][1] - seq[id - 1][pos[msk2][i]][1]);
	return cnt;
}
int main()
{
	{
		int tmp[4] = {0, 1, 2, 3};
		for(int i = 0; i < 24; ++i)
		{
			for(int j = 0; j < 4; ++j)
				pos[i][j] = tmp[j];
			next_permutation(tmp, tmp + 4);
		}
	}
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d", &n);
		for(int i = 0; i < 4; ++i)
			seq[0][i][1] = i + 1;
		for(int i = 1; i <= n; ++i)
		{
			for(int j = 0; j < 4; ++j)
				for(int k = 0; k < 2; ++k)
					scanf("%d", &seq[i][j][k]);
			for(int j = 0; j < 24; ++j)
			{
				f[i][j] = INF;
				if(!valid(i, j))
					continue;
				for(int k = 0; k < 24; ++k)
					f[i][j] = min(f[i][j], f[i - 1][k] + cost(i, j, k));
			}
		}
		ans = INF;
		for(int i = 0 ; i < 24; ++i)
			if(valid(n, i))
				ans = min(ans, f[n][i]);
		printf("%d\n", ans);
	}
	return 0;
}
