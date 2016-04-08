/*
 * 维护s1[k] = ∑num[k]和s2[k] = ∑(n - k + 1) * num[k]
 * 答案为 s2[k] - s1[k] * (n - k) 
 */
#include <cstdio>
int n, m, num[1 << 17];
struct BitTree
{
	long long s[1 << 17];
	void add(int x, long long v) { for ( ; x <= n; x += x & -x) s[x] += v; }
	long long query(int x)
	{
		long long ans = 0;
		for( ; x; x -= x & -x) ans += s[x];
		return ans;
	}
} b[2];
int main()
{
	int i, x;
	char ch[11];
	scanf("%d%d", &n, &m);
	for(i = 1; i <= n; ++i)
	{
		scanf("%d", &num[i]);
		b[0].add(i, num[i]);
		b[1].add(i, (long long)(n - i + 1) * num[i]);
	}
	while(m--)
	{
		scanf("%s%d", ch, &i);
		if(ch[0] == 'Q') printf("%lld\n", b[1].query(i) - b[0].query(i) * (n - i));
		else
		{
			scanf("%d", &x);
			b[0].add(i, x - num[i]);
			b[1].add(i, (long long)(n - i + 1) * (x - num[i]));
			num[i] = x;
		}
	}
	return 0;
}
