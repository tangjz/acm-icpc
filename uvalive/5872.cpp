#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
const int maxn = 26, maxs = 100, Case = 100, mod = 2012182013;
typedef long long LL;
int tt, val[maxn], slen, tlen;
char s[maxs], t[maxs];
int calc(char *ch, int L, int R)
{
	if(L > R)
		return 0;
	int p = 0, q = -1;
	for(int i = R; i >= L; --i)
	{
		if(ch[i] == '(')
			++p;
		else if(ch[i] == ')')
			--p;
		if(!p && q == -1)
		{
			if(ch[i] == '+' || ch[i] == '-' || ch[i] == '*')
				q = i;
		}
	}
	if(q == -1)
	{
		if(ch[L] == '(' && ch[R] == ')')
			return calc(ch, L + 1, R - 1);
		if(ch[L] >= 'a' && ch[L] <= 'z')
			return val[ch[L] - 'a'];
		return ch[L] - '0';
	}
	if(ch[q] == '+')
		return ((LL)calc(ch, L, q - 1) + calc(ch, q + 1, R)) % mod;
	if(ch[q] == '-')
		return ((LL)calc(ch, L, q - 1) - calc(ch, q + 1, R) + mod) % mod;
	return (LL)calc(ch, L, q - 1) * calc(ch, q + 1, R) % mod;
}
int main()
{
	srand(time(0));
	scanf("%d\n", &tt);
	while(tt--)
	{
		int i, j;
		gets(s);
		gets(t);
		for(i = 0, j = 0; s[i]; ++i)
		{
			if(s[i] == ' ' || s[i] == '\t')
				continue;
			if(s[i] >= 'A' && s[i] <= 'Z')
				s[i] = s[i] - 'A' + 'a';
			s[j++] = s[i];
		}
		s[j] = '\0';
		slen = j;
		for(i = 0, j = 0; t[i]; ++i)
		{
			if(t[i] == ' ' || t[i] == '\t')
				continue;
			if(t[i] >= 'A' && t[i] <= 'Z')
				t[i] = t[i] - 'A' + 'a';
			t[j++] = t[i];
		}
		t[j] = '\0';
		tlen = j;
		bool flag = 0;
		for(i = 0; i < Case; ++i)
		{
			for(j = 0; j < 26; ++j)
				val[j] = (LL)rand() * rand() % mod;
			if(calc(s, 0, slen - 1) != calc(t, 0, tlen - 1))
			{
				flag = 1;
				break;
			}
		}
		puts(!flag ? "YES" : "NO");
	}
	return 0;
}
