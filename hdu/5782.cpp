#include <bitset>
#include <stdio.h>
#include <cstring>
#include <algorithm>
const int maxn = 10001;
int n, f[maxn], g[maxn], ord[maxn];
char s[maxn], t[maxn];
std::bitset<maxn> msk[maxn], cur, ans;
inline void getF(int n, char pat[], int m, char tex[], int f[])
{
	static int z[maxn];
	for(int i = 1, L, R = 1; i < n; ++i)
	{
		if(i < R && i + z[i - L] < R)
		{
			z[i] = z[i - L];
			continue;
		}
		int x = std::max(i, R);
		for( ; pat[x] == pat[x - i]; ++x);
		if((z[i] = x - i) > 0)
		{
			L = i;
			R = x;
		}
	}
	for(int i = 0, L, R = 0; i <= m; ++i)
	{
		if(i < R && i + z[i - L] < R)
		{
			f[i] = z[i - L];
			continue;
		}
		int x = std::max(i, R);
		for( ; tex[x] && tex[x] == pat[x - i]; ++x);
		if((f[i] = x - i) > 0)
		{
			L = i;
			R = x;
		}
	}
}
bool cmp(const int &x, const int &y)
{
	return g[x] > g[y];
}
int main()
{
	for(int i = 1; i < maxn; ++i)
	{
		msk[i] = msk[i - 1];
		msk[i].set(i);
	}
	while(scanf("%s%s", s, t) == 2)
	{
		n = strlen(s);
		getF(n, t, n, s, f);
		getF(n, s, n, t, g);
		for(int i = 0; i <= n; ++i)
			ord[i] = i;
		std::sort(ord, ord + n + 1, cmp);
		cur.reset();
		ans.reset();
		for(int i = n, j = 0; i >= 0; --i)
		{
			for( ; j <= n && g[ord[j]] >= i; cur.set(ord[j++]));
			ans <<= 1;
			ans |= cur & msk[f[i]];
		}
		for(int i = 1; i <= n; ++i)
			s[i - 1] = '0' + (int)ans.test(i);
		puts(s);
	}
	return 0;
}
