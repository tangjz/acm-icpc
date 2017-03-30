#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 101, maxm = 15361, maxd = 65, maxv = 7, mod = 1000000009;
int tot, state[maxd], idx[maxd]; // min rep
inline int state_to_index(int seq[])
{
	int mask = 0, cnt = 0;
	for(int i = 0; i < 4; ++i)
		seq[i] += maxv;
	for(int i = 0; i < 4; ++i)
		if(seq[i] >= cnt)
		{
			for(int j = 3; j >= i; --j)
				if(seq[i] == seq[j])
					seq[j] = cnt;
			++cnt;
		}
	for(int i = 1; i < 4; ++i)
		mask = mask << 2 | seq[i];
	if(idx[mask] == -1)
	{
		idx[mask] = tot;
		state[tot++] = mask;
	}
	return idx[mask];
}
inline void index_to_state(int id, int seq[])
{
	int mask = state[id];
	for(int i = 3; i >= 0; --i, mask >>= 2)
		seq[i] = mask & 3;
}
int n, m, f[maxn][maxm], ans;
int g[maxv][maxv], val[maxv];
inline void get_state(int mask)
{
	for(int i = 2; i >= 0; --i, mask >>= 2)
		g[2][i] = mask & 3;
	for(int i = 1; i >= 0; --i, mask >>= 2)
		g[i][2] = mask & 3;
	index_to_state(mask, val);
}
int main()
{
	memset(idx, -1, sizeof idx);
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j < 4; ++j)
			for(int k = 0; k < 4; ++k)
				for(int l = 0; l < 4; ++l)
				{
					int seq[maxv] = {i, j, k, l};
					state_to_index(seq);
				}
	scanf("%d%d", &n, &m);
	f[0][3] = 1; // (0 \\ 0 \\ 0 & 0 & 3, 0000) = 1
	for(int i = 0; i < n; ++i)
		for(int S = 0; S < maxm; ++S)
		{
			if(!f[i][S])
				continue;
			get_state(S);
			int sz = 0, dt = 0;
			bool ban[maxv] = {};
			for(int j = 0; j < 4; ++j)
			{
				if(i <= !(j >> 1) && !ban[val[j]]) // careful with i <= 1
				{
					ban[val[j]] = 1;
					++dt;
				}
				for( ; sz <= val[j]; ++sz);
			}
			for(val[4] = 0; val[4] <= sz && val[4] < m + dt; ++val[4]) // select color for a[i+1]
			{
				if(ban[val[4]])
					continue;
				int c = val[4] == sz, way = val[4] < sz ? f[i][S] : (LL)f[i][S] * (m + dt - sz) % mod;
				for(val[5] = 0; val[5] <= sz + c && val[5] < m + dt; ++val[5]) // select color for b[i+1]
				{
					if(ban[val[5]])
						continue;
					int ways = val[5] < sz + c ? way : (LL)way * (m + dt - sz - c) % mod; // careful with c = 0
					// change g[i][j] where max(i, j) = 3
					int seq[maxv] = {val[2], val[3], val[4], val[5]};
					int T = state_to_index(seq);
					for(int o = 1; o < 3; ++o)
					{
						g[o][3] = 0;
						if(val[(o - 1) << 1] == val[5])
							g[o][3] = g[o - 1][2];
						else
							g[o][3] = max(g[o][3], max(g[o - 1][3], g[o][2] - (o < 3)));
						T = T << 2 | g[o][3];
					}
					for(int o = 1; o <= 3; ++o)
					{
						g[3][o] = 0;
						if(val[4] == val[(o << 1) - 1])
							g[3][o] = g[2][o - 1];
						else
							g[3][o] = max(g[3][o], max(g[2][o] - (o < 3), g[3][o - 1])); // careful with o = 3
						T = T << 2 | g[3][o];
					}
					if(g[3][3] && (f[i + 1][T] += ways) >= mod)
						f[i + 1][T] -= mod;
				}
			}
		}
	for(int S = 0; S < maxm; ++S)
		if(f[n][S] && (ans += f[n][S]) >= mod)
			ans -= mod;
	printf("%d\n", ans);
	return 0;
}
