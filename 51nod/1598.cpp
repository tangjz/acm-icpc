#include <stdio.h>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 100010;
int n, a[maxn], b[maxn], ord[maxn], p[maxn], bitk[maxn], sk;
LL bitb[maxn], sb;
bool cmp(const int &x, const int &y)
{
	return (LL)a[x] * b[y] < (LL)a[y] * b[x];
}
template<class T> void add(T bit[], int x, int v)
{
	for( ; x <= n; x += x & -x)
		bit[x] += v;
}
template<class T> T sum(T bit[], int x)
{
	T ret = 0;
	for( ; x > 0; x -= x & -x)
		ret += bit[x];
	return ret;
}
int main()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d", a + i, b + i);
		if(a[i] < 0)
		{
			a[i] = -a[i];
			b[i] = -b[i];
		}
		if(!a[i] && b[i] < 0)
			b[i] = -b[i];
		ord[i] = i;
	}
	sort(ord + 1, ord + n + 1, cmp);
	for(int i = 1; i <= n; ++i)
		p[ord[i]] = i;
	for(int i = 1; i <= n; ++i)
	{
		add(bitk, p[i], a[i]);
		sk += a[i];
		add(bitb, p[i], b[i]);
		sb += b[i];
		int L = 1, R = n, M;
		while(L < R)
		{
			M = L + R >> 1;
			if(sum(bitk, M) << 1 >= sk)
				R = M;
			else
				L = M + 1;
		}
		int tk = (sum(bitk, L) << 1) - sk;
		LL tb = (sum(bitb, L) << 1) - sb;
		printf("%f\n", tk ? (tb * a[ord[L]] - tk * (LL)b[ord[L]]) / (double)a[ord[L]] : (double)tb);
	}
	return 0;
}
