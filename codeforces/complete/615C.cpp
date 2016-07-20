#include <map>
#include <set>
#include <list>
#include <stack>
#include <queue>
#include <deque>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;
typedef long long LL;
typedef double DB;
typedef long double LDB;
const int maxs = 2222, maxm = 4256233;
const int seed1 = 29, seed2 = 31;
const int mod1 = 998244353, mod2 = 985661441;
int n, m, f[maxs], p[maxs], L[maxs], R[maxs], pw1[maxs], pw2[maxs], g1[maxs], g2[maxs], h1[maxs], h2[maxs], ansL[maxs], ansR[maxs];
char s[maxs], t[maxs];
int tot, lnk[maxm];
struct Hash
{
	int nxt, L, R, v1, v2;
} e[maxs * maxs];
void insert(int l, int r, int a1, int a2)
{
	//printf("ins [%d,%d] : %d, %d\n", l, r, a1, a2);
	int pos = (((LL)a1 << 31LL) ^ a2) % maxm;
	for(int it = lnk[pos]; it != -1; it = e[it].nxt)
		if(e[it].v1 == a1 && e[it].v2 == a2)
			return;
	e[tot] = (Hash){lnk[pos], l, r, a1, a2};
	lnk[pos] = tot++;
}
int idx(int a1, int a2)
{
	//printf("fnd %d, %d\n", a1, a2);
	int pos = (((LL)a1 << 31LL) ^ a2) % maxm;
	for(int it = lnk[pos]; it != -1; it = e[it].nxt)
		if(e[it].v1 == a1 && e[it].v2 == a2)
			return it;
	return -1;
}
int main()
{
	pw1[0] = pw2[0] = 1;
	for(int i = 1; i < maxs; ++i)
	{
		pw1[i] = (LL)pw1[i - 1] * seed1 % mod1;
		pw2[i] = (LL)pw2[i - 1] * seed2 % mod2;
	}
	memset(lnk, -1, sizeof lnk);
	scanf("%s%s", s + 1, t + 1);
	n = strlen(s + 1);
	m = strlen(t + 1);
	for(int i = 1; i <= n; ++i)
	{
		g1[i] = ((LL)g1[i - 1] * seed1 + (s[i] - '0')) % mod1;
		g2[i] = ((LL)g2[i - 1] * seed2 + (s[i] - '0')) % mod2;
	}
	for(int i = 1; i <= n + 1 >> 1; ++i)
		swap(s[i], s[n - i + 1]);
	for(int i = 1; i <= n; ++i)
	{
		h1[i] = ((LL)h1[i - 1] * seed1 + (s[i] - '0')) % mod1;
		h2[i] = ((LL)h2[i - 1] * seed2 + (s[i] - '0')) % mod2;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = i; j <= n; ++j)
		{
			int val11 = g1[j] - (LL)g1[i - 1] * pw1[j - i + 1] % mod1, val12 = h1[j] - (LL)h1[i - 1] * pw1[j - i + 1] % mod1;
			if(val11 < 0)
				val11 += mod1;
			if(val12 < 0)
				val12 += mod1;
			int val21 = g2[j] - (LL)g2[i - 1] * pw2[j - i + 1] % mod2, val22 = h2[j] - (LL)h2[i - 1] * pw2[j - i + 1] % mod2;
			if(val21 < 0)
				val21 += mod2;
			if(val22 < 0)
				val22 += mod2;
			insert(i, j, val11, val21);
			if(i < j)
				insert(n - i + 1, n - j + 1, val12, val22);
		}
	for(int i = 1; i <= m; ++i)
	{
		g1[i] = ((LL)g1[i - 1] * seed1 + (t[i] - '0')) % mod1;
		g2[i] = ((LL)g2[i - 1] * seed2 + (t[i] - '0')) % mod2;
	}
	for(int i = 1; i <= m; ++i)
	{
		f[i] = -1;
		for(int j = 0; j < i; ++j)
		{
			if(f[j] == -1)
				continue;
			int val1 = g1[i] - (LL)g1[j] * pw1[i - j] % mod1, val2 = g2[i] - (LL)g2[j] * pw2[i - j] % mod2, d;
			if(val1 < 0)
				val1 += mod1;
			if(val2 < 0)
				val2 += mod2;
			//printf("chr [%d, %d] : %d, %d\n", j + 1, i, val1, val2);
			if((d = idx(val1, val2)) != -1 && (f[i] == -1 || f[i] > f[j]))
			{
				p[i] = j;
				L[i] = e[d].L;
				R[i] = e[d].R;
				f[i] = f[j];
			}
		}
		if(f[i] != -1)
			++f[i];
	}
	if(f[m] == -1)
	{
		puts("-1");
		return 0;
	}
	printf("%d\n", f[m]);
	for(int i = 0, o = m; o; ++i, o = p[o])
	{
		ansL[i] = L[o];
		ansR[i] = R[o];
	}
	for(int i = f[m] - 1; i >= 0; --i)
		printf("%d %d\n", ansL[i], ansR[i]);
	return 0;
}
