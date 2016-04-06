#include <cstdio>
const int maxn = 20;
int n, x, f[1 << maxn];
void scan(int &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(int x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int len = 0, buf[8];
	while(x)
	{
		buf[len++] = x % 10;
		x /= 10;
	}
	while(len)
		putchar(buf[--len] + '0');
	putchar('\n');
}
int main()
{
	scan(n);
	while(n--)
	{
		scan(x);
		++f[x];
	}
	for(int i = 0; i < maxn; ++i)
		for(int j = 0; j < 1 << maxn; ++j)
			if(~j & (1 << i))
				f[j] += f[j | (1 << i)];
	for(int i = 0; i <= 1000000; ++i)
		print(f[i]);
	return 0;
}

