#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxm = 26881, mod = (int)1e9 + 7;
int n, m, a[maxn], fa[maxn], lnk[maxn], nxt[maxn], c[maxn], f[maxn];
LL s[maxn], que[maxn];
map<LL, int> Hash;
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		fa[i] = lnk[i] = nxt[i] = -1;
	}
	for(int i = 2; i <= n; ++i) {
		scanf("%d", fa + i);
		nxt[i] = lnk[fa[i]];
		lnk[fa[i]] = i;
	}
	for(int i = n; i >= 1; --i) {
		s[i] += a[i];
		if(fa[i] > 0)
			s[fa[i]] += s[i];
	}
	for(int i = 1; i <= n; ++i)
		++Hash[__gcd(s[i], s[1])];
	m = 0;
	for(auto &it : Hash) {
		que[m] = it.first;
		c[m++] = it.second;
	}
	for(int i = 0; i < m; ++i) {
		int ctr = c[i];
		for(int j = i + 1; j < m; ++j)
			if(que[j] % que[i] == 0)
				ctr += c[j];
		if(ctr * que[i] != s[1])
			continue;
		f[i] = 1;
		for(int j = 0; j < i; ++j)
			if(que[i] % que[j] == 0)
				(f[i] += f[j]) >= mod && (f[i] -= mod);
	}
	printf("%d\n", f[m - 1]);
	return 0;
}
