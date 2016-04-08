/*
ID: tangjin2
LANG: C++
TASK: prefix
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn = 201, maxs = 200002, maxl = 11;
int n, len;
LL seq[maxn];
char str[maxs];
bool f[maxs];
int main()
{
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
	while(scanf("%s", str) == 1 && strcmp(str, ".") != 0)
	{
		LL val = 0;
		for(int i = 0; str[i]; ++i)
			val = val << 5 | (str[i] - 'A' + 1);
		seq[n++] = val;
	}
	sort(seq, seq + n);
	while(scanf("%s", str + 1 + len) != EOF)
		len += strlen(str + 1 + len);
	f[0] = 1;
	for(int i = 1; i <= len; ++i)
	{
		LL val = 0;
		for(int j = 1; j < maxl && j <= i; ++j)
		{
			val |= (LL)(str[i - (j - 1)] - 'A' + 1) << (5 * (j - 1));
			if(f[i - j] && *lower_bound(seq, seq + n, val) == val)
			{
				f[i] = 1;
				break;
			}
		}
	}
	for(int i = len; i >= 0; --i)
		if(f[i])
		{
			printf("%d\n", i);
			break;
		}
	return 0;
}
