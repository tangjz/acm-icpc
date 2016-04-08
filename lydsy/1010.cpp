/*
 * 令f[i]表示第i个物品不与第i+1个物品放在一起，第1～i个物品装入的最小费用。
 * f[i]=min(f[k]+((i-k-1)+(s[i]-s[k])-L)^2)=min(f[k]+((s[i]+i)-(s[k]+k+1+L))^2)
 * 朴素算法O(n^2)，不保证不TLE。将复杂度转化为O(n).
 * 设f[i]应由f[k]转移，j为[0,i)中任意一个不等于k的整数。
 * 因为f[i]由f[k]转移，所以有：f[k]+((s[i]+i)-(s[k]+k+1+L))^2 <= f[j]+((s[i]+i)-(s[j]+j+1+L))^2
 * 令A[i]=s[i]+i，B[i]=s[i]+i+1+L
 * 则上式化简为 f[k]+(A[i]-B[k])^2 <= f[j]+(A[i]-B[j])^2
 * 整理得：(f[k]+B[k]^2) - (f[j]+B[j]^2) <= 2*A[i]* (B[k]-B[j])
 * 则，当B[k]>B[j]，即k>j时，( (f[k]+B[k]^2) - (f[j]+B[j]^2) ) / (B[k]-B[j]) <=2*A[i]
 * 而，当B[k]<B[j]，即k<j时，( (f[k]+B[k]^2) - (f[j]+B[j]^2) ) / (B[k]-B[j]) >=2*A[i]
 * 若将点(B[i],f[i]+B[i]^2)看作i在坐标系中对应点P(i)，则上式说明，k需要满足：
 * 对于所有0<=j<k，P(j)-P(k)的斜率不超过2*A[i]
 * 对于所有k<j<i，P(k)-P(j)的斜率不小于2*A[i]
 * 用单调队列维护点的下凸性，乱搞即可。
 */
#include <cstdio>
int n, l, q[50001] = {};
long long sum[50001] = {}, f[50001] = {};
inline long long sqr(const long long x) { return x * x; }
bool check(const int i, const int j, const int k) { return ((f[i] + sqr(sum[i])) - (f[k] + sqr(sum[k]))) * (sum[i] - sum[j]) < ((f[i] + sqr(sum[i])) - (f[j] + sqr(sum[j]))) * (sum[i] - sum[k]); }
long long calc(const int i, const int j) { return f[j] + sqr(sum[i] - sum[j] - l); }
int main()
{
	int i, tmp, head = 1, tail = 1;
	scanf("%d%d", &n, &l); ++l;
	for(i = 1; i <= n; ++i)
	{
		scanf("%d", &tmp);
		sum[i] = sum[i - 1] + tmp + 1;
	}
	for(i = 1; i <= n; ++i)
	{
		while(head < tail && calc(i, q[head]) > calc(i, q[head + 1])) ++head;
		f[i] = calc(i, q[head]);
		while(head < tail && check(i, q[tail - 1], q[tail])) --tail;
		q[++tail] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
