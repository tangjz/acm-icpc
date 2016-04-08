/*
 * BabyStep
 */ 
#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
int n, tot = 0, ans;
long long P, B, N;
struct Node { int id; long long val; } baby[100001];
bool cmp(const Node &x, const Node &y) { return x.val < y.val || x.val == y.val && x.id < y.id; }
int lower_bound(long long num)
{
	for(int l = 0, r = tot - 1; l <= r; )
	{
		int m = l + r >> 1;
		if(baby[m].val == num) return baby[m].id;
		if(baby[m].val < num) l = m + 1;
		else r = m - 1;
	}
	return -1;
}
long long pow(long long x, long long y)
{
	long long ans = 1;
	x %= P;
	while(y)
	{
		if(y & 1) ans = ans * x % P;
		x = x * x % P;
		y >>= 1;
	}
	return ans;
}
int main()
{
	int i;
	long long now, tmp;
	while(scanf("%lld%lld%lld", &P, &B, &N) != EOF)
	{
		n = (int)sqrt(P - 1); if(n * n < P - 1) ++n;
		baby[0].id = 0, baby[0].val = 1;
		for(i = 1; i < n; ++i)
		{
			baby[i].id = i;
			baby[i].val = baby[i - 1].val * B % P;
		}
		sort(baby, baby + n, cmp);
		tot = 1;
		for(i = 1; i < n; ++i)
			if(baby[i].val != baby[tot - 1].val) baby[tot++] = baby[i];
		now = N;
		tmp = pow(pow(B, P - 2), (long long)n);
		for(ans = -1, i = 0; i < n; ++i)
		{
			int id = lower_bound(now);
			if(id != -1)
			{
				ans = i * n + id;
				break;
			}
			now = now * tmp % P;
		}
		if(ans == -1) printf("no solution\n");
		else printf("%d\n", ans);
	}
	return 0;
}
