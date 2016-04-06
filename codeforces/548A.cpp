#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1001;
int n, m;
char s[maxn];
bool flag;
int main()
{
	scanf("%s%d", s, &m);
	n = strlen(s);
	if(n % m == 0)
	{
		flag = 1;
		for(int i = 0, j, a, b; i < n; i = j)
		{
			j = i + n / m;
			for(a = i, b = j - 1; a < b; ++a, --b)
				if(s[a] != s[b])
					break;
			if(a < b)
			{
				flag = 0;
				break;
			}
		}
	}
	puts(flag ? "YES" : "NO");
	return 0;
}
