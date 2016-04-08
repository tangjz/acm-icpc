#include <cstdio>
const int maxn = 100001, maxm = 1000001;
int n, a[maxn], c[maxm], lim;
void scan(int &x)
{
	static int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x)
{
	int len = 0, num[5];
	for( ; x; x /= 10)
		num[len++] = x % 10;
	if(!len)
		num[len++] = 0;
	while(len)
		putchar('0' + num[--len]);
	putchar('\n');	
}
int main()
{
	scan(n);
	for(int i = 1; i <= n; ++i)
	{
		scan(a[i]);
		++c[a[i]];
		if(lim < a[i])
			lim = a[i];
	}
	for(int i = lim; i; --i)
		for(int j = i + i; j <= lim; j += i)
			c[j] += c[i];
	for(int i = 1; i <= n; ++i)
		print(c[a[i]] - 1);
	return 0;
}
