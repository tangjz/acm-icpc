#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 5001, maxd = 90, maxt = 5, delta = 100;
int n, a[maxn][4], cnt[3][2], f[2][maxd][maxd][maxd], cur, pre = 1, ans;
inline void upd(int &x, int y)
{
	if(x < y)
		x = y;
}
int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < 3; ++j)
		{
			scanf("%d", a[i] + j);
			if(a[i][j])
				++cnt[j][0];
			if(a[i][j] < 0)
				++cnt[j][1];
		}
	if(cnt[0][1] + cnt[1][1] + cnt[2][1] >= maxd)
	{
		puts("1");
		return 0;
	}
	for(int t0 = 0; t0 <= maxt; ++t0)
	{
		int s0 = 500 * (t0 + 1), L0 = cnt[0][0] - (n >> t0), R0 = cnt[0][0] - (t0 == maxt ? 0 : (n >> t0 + 1) + 1);
		if(L0 > cnt[0][1] || R0 < 0)
			continue;
		if(L0 < 0)
			L0 = 0;
		if(R0 > cnt[0][1])
			R0 = cnt[0][1];
		for(int t1 = 0; t1 <= maxt; ++t1)
		{
			int s1 = 500 * (t1 + 1), L1 = cnt[1][0] - (n >> t1), R1 = cnt[1][0] - (t1 == maxt ? 0 : (n >> t1 + 1) + 1);
			if(L1 > cnt[1][1] || R1 < 0)
				continue;
			if(L1 < 0)
				L1 = 0;
			if(R1 > cnt[1][1])
				R1 = cnt[1][1];
			for(int t2 = 0; t2 <= maxt; ++t2)
			{
				int s2 = 500 * (t2 + 1), L2 = cnt[2][0] - (n >> t2), R2 = cnt[2][0] - (t2 == maxt ? 0 : (n >> t2 + 1) + 1);
				if(L2 > cnt[2][1] || R2 < 0)
					continue;
				if(L2 < 0)
					L2 = 0;
				if(R2 > cnt[2][1])
					R2 = cnt[2][1];
				for(int i = 0; i < n; ++i)
					a[i][3] = (a[i][0] ? s0 * (250 - abs(a[i][0])) / 250 : 0) + (a[i][1] ? s1 * (250 - abs(a[i][1])) / 250 : 0) + (a[i][2] ? s2 * (250 - abs(a[i][2])) / 250 : 0);
				int mx = R0 + R1 + R2, val = a[0][3] + mx * delta;
				memset(f[cur], -1, sizeof f[cur]);
				f[cur][0][0][0] = 0;
				int tot = 0;
				for(int i = 1; i < n; ++i)
				{
					if(a[i][3] <= val)
					{
						++tot;
						continue;
					}
					pre ^= 1;
					cur ^= 1;
					memset(f[cur], -1, sizeof f[cur]);
					int dAL = a[i][0] < 0, dBL = a[i][1] < 0, dCL = a[i][2] < 0;
					for(int A = 0; A <= R0; ++A)
						for(int B = 0; B <= R1; ++B)
							for(int C = 0; C <= R2; ++C)
							{
								if(f[pre][A][B][C] == -1)
									continue;
								for(int dA = 0; dA <= dAL; ++dA) if(A + dA <= R0)
									for(int dB = 0; dB <= dBL; ++dB) if(B + dB <= R1)
										for(int dC = 0; dC <= dCL; ++dC) if(C + dC <= R2)
											upd(f[cur][A + dA][B + dB][C + dC], f[pre][A][B][C] + (a[i][3] - (dA ? s0 * (250 + a[i][0]) / 250 : 0) - (dB ? s1 * (250 + a[i][1]) / 250 : 0) - (dC ? s2 * (250 + a[i][2]) / 250 : 0) <= val));
							}
				}
				for(int A = 0; A <= R0; ++A)
					for(int B = 0; B <= R1; ++B)
						for(int C = 0; C <= R2; ++C)
							upd(ans, f[cur][A][B][C] + tot);
			}
		}
	}
	printf("%d\n", n - ans);
	return 0;
}
