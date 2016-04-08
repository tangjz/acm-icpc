#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 131072;
int t, n, resL[maxn << 1], ans_L, ans_R;
long long r, h[maxn], seg[maxn << 1], ans;
void update(long long tmp, int L, int R)
{
	if(L > R)
		swap(L, R);
	if(tmp > ans || tmp == ans && (L < ans_L || L == ans_L && R < ans_R))
	{
		ans = tmp;
		ans_L = L;
		ans_R = R;
	}
}
inline int id(int L, int R)
{
	return L + R | L != R;
}
void build(int L, int R, int flag)
{
	if(L == R)
	{
		seg[id(L, R)] = h[L] + L * r * flag;
		resL[id(L, R)] = L;
		return;
	}
	int M = L + R >> 1;
	build(L, M, flag);
	build(M + 1, R, flag);
	if(seg[id(L, M)] >= seg[id(M + 1, R)])
		resL[id(L, R)] = resL[id(L, M)];
	else
		resL[id(L, R)] = resL[id(M + 1, R)];
	seg[id(L, R)] = max(seg[id(L, M)], seg[id(M + 1, R)]);
}
int get_l(int L, int R, int l, int r)
{
	if(l <= L && R <= r)
		return resL[id(L, R)];
	int M = L + R >> 1;
	if(r <= M)
		return get_l(L, M, l, r);
	else if(l > M)
		return get_l(M + 1, R, l, r);
	else
	{
		int res1 = get_l(L, M, l, r);
		int res2 = get_l(M + 1, R, l, r);
		if(seg[id(res1, res1)] >= seg[id(res2, res2)])
			return res1;
		else
			return res2;
	}
}
int main()
{
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case)
	{
		printf("Case #%d:\n", Case);
		scanf("%d%I64d", &n, &r);
		for(int i = 1; i <= n; ++i)
			scanf("%I64d", h + i);
		ans = 0;
		build(1, n, 1);
		for(int i = 1; i <= n; ++i)//i<=j<=i+n/2 or j <= i-n/2
			if(i <= n / 2)
			{
				int tmp_L = i;
				int tmp_R = get_l(1, n, i + 1, i + n / 2);
				long long tmp = h[tmp_L] - tmp_L * r + h[tmp_R] + tmp_R * r;
				update(tmp, tmp_L, tmp_R);
			}
			else if(i > (n + 1) / 2)
			{
				int tmp_L = i;
				int tmp_R = get_l(1, n, 1, i - (n + 1) / 2);
				long long tmp = h[tmp_L] - tmp_L * r + h[tmp_R] + tmp_R * r + n * r;
				update(tmp, tmp_L, tmp_R);
			}
		build(1, n, -1);
		for(int i = 1; i <= n; ++i)//i-n/2 <= j <= i or i+n/2 <= j
			if(i + (n + 1) / 2 <= n)
			{
				int tmp_L = i;
				int tmp_R = get_l(1, n, i + (n + 1) / 2, n);
				long long tmp = h[tmp_L] + tmp_L * r + h[tmp_R] - tmp_R * r + n * r;
				update(tmp, tmp_L, tmp_R);
			}
			else if(i > n / 2)
			{
				int tmp_L = i;
				int tmp_R = get_l(1, n, i - n / 2, i - 1);
				long long tmp = h[tmp_L] + tmp_L * r + h[tmp_R] - tmp_R * r;
				update(tmp, tmp_L, tmp_R);
			}
		printf("%d %d\n", ans_L, ans_R);
	}
	return 0;
}
