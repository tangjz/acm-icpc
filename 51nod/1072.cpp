#include <cmath>
#include <stdio.h>
int t, a, b;
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d%d", &a, &b);
		if(a > b)
		{
			a = a + b;
			b = a - b;
			a = a - b;
		}
		puts(a != (int)((b - a) * (1 + sqrt(5)) * 0.5) ? "A" : "B");
	}
	return 0;
}
