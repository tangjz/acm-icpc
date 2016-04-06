#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 21, maxw = 16000;
int n, m, row[maxn], col[maxn];
LL seq[maxn * maxn];
bool vis[maxw];
inline int random()
{
	return (rand() & ((1 << 20) - 1)) % maxw + 1;
}
inline bool isSquare(LL x)
{
	LL r = (LL)sqrt(x);
	for( ; r * r > x; --r);
	for( ; (r + 1) * (r + 1) <= x; ++r);
	return r * r == x;
}
void build(int len, int num[])
{
	while(1)
	{
		LL sum = 0;
		for(int i = 1; i < len; ++i)
		{
			for(num[i] = random(); vis[num[i]]; num[i] = random());
			vis[num[i]] = 1;
			sum += num[i] * num[i];
		}
		for(int i = 1; i < maxw; ++i)
			if(!vis[i] && isSquare(sum + i * i))
			{
				vis[i] = 1;
				num[0] = i;
				break;
			}
		if(num[0])
			break;
		for(int i = 1; i < len; ++i)
			vis[num[i]] = 0;
	}
	for(int i = 0; i < len; ++i)
		num[i] *= num[i];
}
int main()
{
	srand(time(NULL));
	scanf("%d%d", &m, &n);
	while(1)
	{
		memset(vis, 0, sizeof vis);
		build(n, row);
		build(m, col);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				seq[i * m + j] = (LL)row[i] * col[j];
		sort(seq, seq + n * m);
		if(unique(seq, seq + n * m) - seq == n * m)
			break;
	}
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			printf("%lld%c", (LL)row[i] * col[j], " \n"[j == m - 1]);
	return 0;
}
