#include <cstdio>
int ch;
void read(int &t)
{
	while((ch = getchar()) < '0' || ch > '9');
	t = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		t = (t << 3) + (t << 1) + ch - '0';
}
int len, p[3];
void write(int t)
{
	while(t)
	{
		p[len++] = t % 10;
		t /= 10;
	}
	while(len) putchar(p[--len] + '0');
}
int n, val[101], x;
int main()
{
	while(scanf("%d", &n) != EOF)
	{
		while(n--)
		{
			read(x);
			++val[x];
		}
		bool flag = 0;
		for(x = 1; x <= 100; ++x)
			if(val[x])
				while(val[x])
				{
					flag == 0 ? flag = 1 : putchar(' ');
					write(x);
					--val[x];
				}
		putchar('\n');
	}
	return 0;
}
