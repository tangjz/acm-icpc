#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int maxn = 200001, maxm = 451, maxc = 1351;
int n, m, q, a[maxn], ord[maxn];
int sz, tot, cnt[maxm], pos[maxm][maxc];
int qL[maxn], qR[maxn], mx[maxm][maxc], fir[maxm][maxc];
int seq[maxn], dt[maxc], ans;
bool cmp(int const &x, int const &y)
{
	return a[x] > a[y];
}
int main()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d", a + i);
		ord[i] = i;
	}
	std::sort(ord + 1, ord + n + 1, cmp);
	sz = (int)ceil(sqrt(n));
	for(int i = 1; i <= n; i += sz, ++tot)
	{
		int L = i, R = std::min(i + sz - 1, n);
		cnt[tot] = 0;
		for(int j = 1; j <= n; j += sz)
			pos[tot][cnt[tot]++] = j;
		pos[tot][cnt[tot]++] = n + 1;
		for(int j = L; j <= R; ++j)
		{
			pos[tot][cnt[tot]++] = (qL[j] = std::max(1, ord[j] - m + 1));
			pos[tot][cnt[tot]++] = (qR[j] = ord[j] + 1);
		}
		std::sort(pos[tot], pos[tot] + cnt[tot]);
		cnt[tot] = std::unique(pos[tot], pos[tot] + cnt[tot]) - pos[tot];
		memset(dt, 0, cnt[tot] * sizeof(int));
		for(int j = L; j <= R; ++j)
		{
			qL[j] = std::lower_bound(pos[tot], pos[tot] + cnt[tot], qL[j]) - pos[tot];
			qR[j] = std::lower_bound(pos[tot], pos[tot] + cnt[tot], qR[j]) - pos[tot];
			++dt[qL[j]];
			--dt[qR[j]];
		}
		for(int j = 0; j + 1 < cnt[tot]; ++j)
		{
			int pL = pos[tot][j], pR = pos[tot][j + 1];
			for(fir[tot][j] = mx[tot][j] = seq[pL++]; pL < pR; ++pL)
				if(mx[tot][j] < seq[pL])
					mx[tot][j] = seq[pL];
			for(pL = pos[tot][j]; pL < pR; ++pL)
				seq[pL] += dt[j];
			dt[j + 1] += dt[j];
		}
	}
	scanf("%d", &q);
	while(q--)
	{
		int L, R, idx;
		scanf("%d%d%d", &L, &R, a + 0);
		a[0] ^= ans;
		idx = std::upper_bound(ord + 1, ord + n + 1, 0, cmp) - ord - 1;
		int blk = std::min(idx / sz, tot - 1);
		memset(dt, 0, cnt[blk] * sizeof(int));
		for(int i = blk * sz + 1; i <= idx; ++i)
		{
			++dt[qL[i]];
			--dt[qR[i]];
		}
		ans = 0;
		for(int i = 0; i + 1 < cnt[blk]; ++i)
		{
			dt[i + 1] += dt[i];
			if(L <= pos[blk][i] && pos[blk][i + 1] <= R + 1)
				ans = std::max(ans, mx[blk][i] + dt[i]);
			else if(pos[blk][i] <= R && L < pos[blk][i + 1])
				for(int j = pos[blk][i], val = fir[blk][i] + dt[i]; j < pos[blk][i + 1]; ++j)
				{
					if(j > R)
						break;
					else if(j >= L)
						ans = std::max(ans, val);
					val -= (a[j] >= a[0]);
					val += (a[j + m] >= a[0]);
				}
		}
		printf("%d\n", ans = m - ans);
	}
	return 0;
}
