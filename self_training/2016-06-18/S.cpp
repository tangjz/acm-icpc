#include <cstdio>
const int maxn = 100001;
int tt, pos;
char s[maxn], t[maxn];
int main()
{
	scanf("%d", &tt);
	while(tt--)
	{
		scanf("%s%s", s, t);
		pos = 0;
		for(int i = 0; s[i]; ++i)
			if(s[i] == t[pos])
				++pos;
		puts(!t[pos] ? "YES" : "NO");
	}
	return 0;
}
