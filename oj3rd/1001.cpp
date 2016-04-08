#include <cstdio>
int m;
long long n, x;
char s[50];
template<class T>
void scan(T &x)
{
	char ch;
	while((ch = getchar()) < '0' || ch > '9');
	x = ch - '0';
	while((ch = getchar()) >= '0' && ch <= '9')
		x = (x << 3) + (x << 1) + (ch - '0');
}
int main()
{
	while(scanf("%lld", &n) == 1)
	{
		for(int i = 0; i < 3; ++i)
		{
			scan(m);
			for(int i = 0; i < m; ++i)
			{
				s[i] = getchar();
				getchar();
			}
			for(int i = 0; i < m; ++i)
			{
				scan(x);
				if(s[i] == '1')
					if(n >= x)
						n -= x;
					else
						n = -1;
			}
		}
		puts(n == -1 ? "run away!" : "YES!");
	}
	return 0;
}
