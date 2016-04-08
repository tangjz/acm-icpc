#include <cstdio>
long long t, n;
void scan(long long &x)
{
	int ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
void print(long long x)
{
	if(!x)
	{
		puts("0");
		return;
	}
	int len = 0, buf[18];
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
	scan(t);
	while(t--)
	{
		scan(n);
		print(n * 2);
	}
	return 0;
}

