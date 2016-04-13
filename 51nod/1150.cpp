#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 50001, maxd = 61, maxe = 20;
int n, Log10[maxd];
LL a[maxn], pw10[maxe], ans;
int find(int L, int R, int dep)
{
	while(L < R)
	{
		int M = L + R >> 1;
		if(a[M] & (1LL << dep))
			R = M;
		else
			L = M + 1;
	}
	return a[L] & (1LL << dep) ? L : L + 1;
}
void solve_2(int dep, int len, int L0, int R0, int L1, int R1)
{
	if(L0 > R0 || L1 > R1)
		return;
	if(dep < 0)
	{
		ans += (R0 - L0 + 1) * (R1 - L1 + 1) * len;
		return;
	}
	int M0 = find(L0, R0, dep);
	int M1 = find(L1, R1, dep);
	if(pw10[len] & (1LL << dep))
	{
		ans += ((LL)(M0 - L0) * (M1 - L1) + (R0 - M0 + 1LL) * (R1 - M1 + 1)) * (len - 1);
		solve_2(dep - 1, len, L0, M0 - 1, M1, R1);
		solve_2(dep - 1, len, M0, R0, L1, M1 - 1);
 	}
	else
	{
		ans += ((M0 - L0) * (R1 - M1 + 1LL) + (R0 - M0 + 1LL) * (M1 - L1)) * len;
		solve_2(dep - 1, len, L0, M0 - 1, L1, M1 - 1);
		solve_2(dep - 1, len, M0, R0, M1, R1);
	}
}
void solve_1(int dep, int L, int R)
{
	if(dep < 3 || L >= R)
		return;
	int M = find(L, R, dep);
	if(L < M && M <= R)
	{
		if(Log10[dep] >= 0)
			ans += (M - L) * (R - M + 1LL) * (Log10[dep] - 1);
		else
			solve_2(dep - 1, -Log10[dep], L, M - 1, M, R);
	}
	solve_1(dep - 1, L, M - 1);
	solve_1(dep - 1, M, R);
}
int main()
{
	pw10[0] = 1;
	for(int i = 1; i < maxe; ++i)
		pw10[i] = pw10[i - 1] * 10;
	for(int i = 1; i < maxd; ++i)
	{
		for(Log10[i] = Log10[i - 1]; pw10[Log10[i]] < 1LL << i; ++Log10[i]);
		if(Log10[i - 1] < Log10[i])
			Log10[i - 1] = -Log10[i - 1];
	}
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%lld", a + i);
	sort(a, a + n);
	solve_1(maxd - 1, 0, n - 1);
	printf("%lld\n", ans << 1);
	return 0;
}
