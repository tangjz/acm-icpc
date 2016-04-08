#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int n, v[maxn], cnt, l, r;
char s[maxn], t[maxn];
int main()
{
	scanf("%d%s%s", &n, s, t);
	for(int i = 0; i <= n; ++i)
		v[i] = s[i] == t[i];
	l = n, r = 0;
	for(int i = 0; i <= n; ++i)
		if(!v[i])
		{
			l = min(l, i);
			r = max(r, i);
		}
	bool flag1 = 1, flag2 = 1;
	for(int i = l + 1; i <= r; ++i)
	{
		flag1 &= s[i] == t[i - 1];
		flag2 &= s[i - 1] == t[i];
	}
	printf("%d\n", (int)flag1 + (int)flag2);
	return 0;
}
