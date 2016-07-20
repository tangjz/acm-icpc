#include <cstdio>
#include <algorithm>
int a, b, c;
int main()
{
	while(scanf("%d%d%d", &a, &b, &c) == 3 && a + b + c)
		if(a == b && b == c)
		{
			if(a + 1 <= 13)
				printf("%d %d %d\n", a + 1, b + 1, c + 1);
			else
				puts("*");
		}
		else if(a == b || a == c || b == c)
		{
			if(a != b)
				std::swap(a != c ? a : b, c);
			if(c + 1 != a && c + 1 <= 13)
				++c;
			else if(c + 2 <= 13)
				c += 2;
			else if(a + 1 <= 13)
			{
				++a;
				++b;
				c = 1;
			}
			else
				a = b = c = 1;
			if(a > c)
				std::swap(a, c);
			printf("%d %d %d\n", a, b, c);
		}
		else
			printf("%d %d %d\n", 1, 1, 2);
	return 0;
}
