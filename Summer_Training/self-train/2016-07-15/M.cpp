#include <cstdio>
const int maxn = 1000001;
int m, n, a[maxn], tot, b[maxn], sg, cnt;
int main()
{
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);
	if(a[n - 1] == m - 1)
	{
		for(int i = n - 1; i >= 0 && a[n - 1] - a[i] == n - 1 - i; --i, ++cnt);
		printf("%d\n", cnt);
		return 0;
	}
	for(int i = 0; i < n; ++i)
	{
		a[i] = m - 1 - a[i] - (n - i);
		if(!a[i])
			break;
		if(!i || a[tot - 1] > a[i])
			a[tot++] = a[i];
		++b[tot - 1];
	}
	for(int i = 0; i < tot; ++i)
		if(a[i] & 1)
			sg ^= b[i];
	for(int i = 0; i < tot; ++i)
		if(a[i] & 1)
		{
			if((sg ^ b[i]) < b[i])
				++cnt;
		}
		else
		{
			int last = i + 1 < tot && a[i + 1] == a[i] - 1 ? b[i + 1] : 0;
			if((sg ^ last) > last && (sg ^ last) <= last + b[i])
				++cnt;
		}
	printf("%d\n", cnt);
	return 0;
}
