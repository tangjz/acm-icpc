#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 200010;
int len, n, flag, delta;
char str[maxn];
void reverse(int l, int r)
{
	for(int i = 0; l + i < r - i; ++i)
		swap(str[l + i], str[r - i]);
}
int main()
{
	gets(str);
	scanf("%d", &n);
	{
		len = strlen(str);
		flag = -1;
		delta = 0;
		while(n--)
		{
			int x;
			scanf("%d", &x);
			flag = -flag;
			delta = (delta + flag * x) % len;
			if(delta < 0)
				delta += len;
		}
		reverse(0, delta - 1);
		reverse(delta, len - 1);
		if(flag < 0)
			reverse(0, len - 1);
		puts(str);
	}
	return 0;
}
