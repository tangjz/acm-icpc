#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

long long a1, a2, a3, ans;

int main()
{
	scanf("%lld %lld %lld", &a1, &a2, &a3);
	if(a1)
	{
		if(a1 + 2 * a2 >= 2)
			ans = a1 + 2 * a2 + 3 * a3;
		else
			ans = 2 * a3 + 1;
	}
	else
	{
		if(a3)
		{
			if(a2 >= 2)
				ans = 2 * (a2 - 1) + 3 * a3;
			else if(a2)
				ans = 2 * a3 + 1;
			else
				ans = a3;
		}
		else
			ans = a2;
	}
	printf("%lld\n", ans);
}
