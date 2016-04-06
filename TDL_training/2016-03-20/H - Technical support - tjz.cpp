#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200001;
int a, flag, tot, val[maxn];
int main()
{
	scanf("%d", &a);
	++a;
	if(a == 0)
	{
		puts("infinity");
		return 0;
	}
	if(a < 0)
	{
		a = -a;
		flag = 1;
	}
	for(int i = 1; i <= a / i; ++i)
		if(a % i == 0)
		{
			if(flag)
			{
				val[tot++] = a / i - i;
				val[tot++] = i - a / i;
			}
			else
			{
				val[tot++] = i + a / i;
				val[tot++] = -i - a / i;
			}
		}
	sort(val, val + tot);
	tot = unique(val, val + tot) - val;
	printf("%d\n", tot);
	return 0;
}
