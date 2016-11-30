#include <cstdio>
#include <algorithm>
using namespace std;
int t, n, a, b;
char str[100];
int main()
{
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d", &n);
		a = b = 1500;
		while(n--)
		{
			scanf("%s", str);
			if(str[0] == 'g')
				a += 100;
			else
				a -= 100;
			if(a > 3299)
				a = 3299;
			else if(a < 0)
				a = 0;
			if(a > b)
				swap(a, b);
		}
		printf("%d\n", b);
	}
	return 0;
}
