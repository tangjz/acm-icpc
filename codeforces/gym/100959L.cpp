#include <cstdio>
#include <cstring>
const int maxn = 5001;
int slen, tlen;
char s[maxn], t[maxn];
int main()
{
	scanf("%s%s", s, t);
	slen = strlen(s);
	tlen = strlen(t);
	int last = -1, now = 0;
	for(int i = 0; i < tlen; ++i)
	{
		if(now < slen && s[now] == t[i])
			++now;
		else if(last == -1)
		{
			puts("No");
			return 0;
		}
		if(t[i] != t[i + 1])
			last = i;
	}
	puts(now == slen ? "Yes" : "No");
	return 0;
}
