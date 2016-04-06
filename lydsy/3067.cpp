#include <stdio.h>
typedef long long LL;
const int maxn = 300002, mod = 1 << 23;
int n, tot, pre[mod];
LL now, ans;
char str[maxn];
struct Hash
{
	int nxt, cnt;
	LL val;
} e[maxn];
void insert(LL x)
{
	int pos = x & (mod - 1);
	for(int it = pre[pos]; it; it = e[it].nxt)
		if(e[it].val == x)
		{
			++e[it].cnt;
			return;
		}
	e[++tot] = (Hash){pre[pos], 1, x};
	pre[pos] = tot;
}
int find(LL x)
{
	int pos = x & (mod - 1);
	for(int it = pre[pos]; it; it = e[it].nxt)
		if(e[it].val == x)
			return e[it].cnt;
	return 0;
}
int main()
{
	scanf("%d%s", &n, str);
	insert(0);
	for(int i = 0; i < n; ++i)
	{
		if(str[i] <= 'Z')
			now ^= 1LL << str[i] - 'A';
		else
			now ^= 1LL << str[i] - 'a' + 26;
		ans += find(now);
		for(int j = 0; j < 52; ++j)
			ans += find(now ^ (1LL << j));
		insert(now);
	}
	printf("%lld\n", ans);
	return 0;
}
