#include <cstdio>
int t, n, x, a, b;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		a = b = 0;
		scanf("%d", &n);
		while(n--)
		{
			scanf("%d", &x);
			switch(x) {
				case 1 : {
					++a;
					break;
				}
				case 2 : {
					++b;
					break;
				}
				case 3 : {
					++a;
					++b;
					break;
				}
				case 4 : {
					--a;
					--b;
					break;
				}
			}
		}
		puts(a > b ? "Kobayashi" : (a < b ? "Tohru" : "Draw"));
	}
	return 0;
}
