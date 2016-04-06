#include <cstdio>
const int maxa = 1010, maxb = 101;
int t, n, m, a, b, xa[maxa], ya[maxa], xb[maxb], yb[maxb], xL, xR, yL, yR, dis;
int abs(int x)
{
	return x < 0 ? -x : x;
}
long long cnt(int pos, int x[])
{
	long long ret = 0;
	for(int i = 0; i < a; ++i)
		ret += (long long)(pos - x[i]) * (pos - x[i]);
	return ret;
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		scanf("%d%d%d%d", &n, &m, &a, &b);
		for(int i = 0; i < a; ++i)
			scanf("%d%d", xa + i, ya + i);
		for(int i = 0; i < b; ++i)
			scanf("%d%d", xb + i, yb + i);
		int L = 1, R = m;
		while(R - L >= 3)
		{
			int ML = L + (R - L) / 3, MR = R - (R - L) / 3;
			if(cnt(ML, xa) < cnt(MR, xa))
				R = MR;
			else
				L = ML;
		}
		xL = L, xR = R;
		L = 1, R = m;
		while(R - L >= 3)
		{
			int ML = L + (R - L) / 3, MR = R - (R - L) / 3;
			if(cnt(ML, ya) < cnt(MR, ya))
				R = MR;
			else
				L = ML;
		}
		yL = L, yR = R;
		long long ans = (long long)1e18;
		for(int i = xL; i <= xR; ++i)
			for(int j = yL; j <= yR; ++j)
			{
				long long tmp = (long long)1e9;
				for(int k = 0; k < b; ++k)
					if(tmp > abs(i - xb[k]) + abs(j - yb[k]))
						tmp = abs(i - xb[k]) + abs(j - yb[k]);
				tmp += cnt(i, xa) + cnt(j, ya);
				if(ans > tmp)
					ans = tmp;
			}
		printf("Case #%d: %lld\n", Case, ans);
	}
	return 0;
}
