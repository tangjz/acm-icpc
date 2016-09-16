#include <cmath>
#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn = 100010, maxm = 320;
int n, m, sz[maxm], fir[maxm], seq[maxm][maxm], cnt[maxm][maxn], lastans;
int main()
{
	int q, qT, qL, qR, qK;
	scanf("%d", &n);
	m = (int)sqrt(n);
	for(int i = 0; i * m < n; ++i)
		for(int j = 0; j < m && i * m + j < n; ++j)
		{
			scanf("%d", seq[i] + sz[i]);
			++cnt[i][seq[i][sz[i]]];
			++sz[i];
		}
	scanf("%d", &q);
	while(q--)
	{
		scanf("%d%d%d", &qT, &qL, &qR);
		qL = (qL + lastans - 1) % n;
		qR = (qR + lastans - 1) % n;
		if(qL > qR)
			swap(qL, qR);
		int pL = qL / m, pR = qR / m;
		if(qT == 1)
		{
			if(pL == pR)
			{
				int tmp = seq[pL][(qR % m + fir[pL]) % sz[pL]];
				for(int i = qR % m, j = qL % m, cur = (i + fir[pL]) % sz[pL], nxt = (cur - 1 + sz[pL]) % sz[pL]; i > j; --i, cur = nxt, nxt = (nxt - 1 + sz[pL]) % sz[pL])
					seq[pL][cur] = seq[pL][nxt];
				seq[pL][(qL % m + fir[pL]) % sz[pL]] = tmp;
			}
			else
			{
				int tmp = seq[pL][(sz[pL] - 1 + fir[pL]) % sz[pL]];
				--cnt[pL][tmp];
				for(int i = sz[pL] - 1, j = qL % m, cur = (i + fir[pL]) % sz[pL], nxt = (cur - 1 + sz[pL]) % sz[pL]; i > j; --i, cur = nxt, nxt = (nxt - 1 + sz[pL]) % sz[pL])
					seq[pL][cur] = seq[pL][nxt];
				seq[pL][(qL % m + fir[pL]) % sz[pL]] = seq[pR][(qR % m + fir[pR]) % sz[pR]];
				++cnt[pL][seq[pL][(qL % m + fir[pL]) % sz[pL]]];
				for(int i = pL + 1; i < pR; ++i)
				{
					fir[i] = (fir[i] - 1 + sz[i]) % sz[i];
					--cnt[i][seq[i][fir[i]]];
					swap(tmp, seq[i][fir[i]]);
					++cnt[i][seq[i][fir[i]]];
				}
				--cnt[pR][seq[pR][(qR % m + fir[pR]) % sz[pR]]];
				for(int i = qR % m, j = 0, cur = (i + fir[pR]) % sz[pR], nxt = (cur - 1 + sz[pR]) % sz[pR]; i > j; --i, cur = nxt, nxt = (nxt - 1 + sz[pR]) % sz[pR])
					seq[pR][cur] = seq[pR][nxt];
				seq[pR][fir[pR]] = tmp;
				++cnt[pR][tmp];
			}
		}
		else
		{
			int ans = 0;
			scanf("%d", &qK);
			qK = (qK + lastans - 1) % n + 1;
			if(pL == pR)
				for(int i = qL % m, j = qR % m, o = (i + fir[pL]) % sz[pL]; i <= j; ++i, o = (o + 1) % sz[pL])
					ans += seq[pL][o] == qK;
			else
			{
				for(int i = qL % m, j = sz[pL] - 1, o = (i + fir[pL]) % sz[pL]; i <= j; ++i, o = (o + 1) % sz[pL])
					ans += seq[pL][o] == qK;
				for(int i = 0, j = qR % m, o = fir[pR]; i <= j; ++i, o = (o + 1) % sz[pL])
					ans += seq[pR][o] == qK;
				for(int i = pL + 1; i < pR; ++i)
					ans += cnt[i][qK];
			}
			printf("%d\n", ans);
			lastans = ans;
		}
	}
	return 0;
}
