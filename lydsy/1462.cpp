#include <bits/stdc++.h>
using namespace std;
namespace fastIO{
	#define BUF_SIZE 1000001
	bool IOerror = 0;
	inline char next() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf, pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) return IOerror = 1, -1;
		}
		return *(p1++);
	}
	inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
	inline void read(int &x) {
		bool sign = 0; char ch = next(); x = 0;
		for( ; blank(ch); ch = next());
		if(IOerror) return;
		if(ch == '-') sign = 1, ch = next();
		for( ; ch >= '0' && ch <= '9'; x = x * 10 + (ch - '0'), ch = next());
		if(sign) x = -x;
	}
	#undef BUF_SIZE
}
const int maxn = (int)1e5 + 1, maxv = 27;
int t, n, m, a[maxn], b[maxn], les[maxn], eq[maxn], gre[maxn], fail[maxn], ans;
int pos[maxv + 2], pL[maxv + 2], pR[maxv + 2];
inline bool match(int pos, int *txt) {
	return (les[pos] == -1 || txt[les[pos]] < txt[pos])
		&& (eq[pos] == -1 || txt[eq[pos]] == txt[pos])
		&& (gre[pos] == -1 || txt[gre[pos]] > txt[pos]);
}
int main() {
	fastIO::read(t);
	while(t--) {
		fastIO::read(m), fastIO::read(n);
		memset(pos, -1, sizeof pos);
		for(int i = 0; i < m; ++i) {
			int &x = b[i];
			fastIO::read(x);
			eq[i] = pos[x];
			pos[x] = i;
		}
		int las = 0;
		for(int i = 1; i < maxv; ++i)
			if(pos[i] != -1) {
				pL[i] = las;
				pR[las] = i;
				las = i;
			}
		pL[maxv] = las;
		pR[las] = maxv;
		for(int i = m - 1; i >= 0; --i) {
			int x = b[i];
			pos[x] = eq[i];
			if(pos[x] == -1) {
				pL[pR[x]] = pL[x];
				pR[pL[x]] = pR[x];
			}
			les[i] = pos[pL[x]];
			gre[i] = pos[pR[x]];
		}
		for(int i = 1, j = 0; i < m; ++i) {
			while(j && !match(j, b + i - j))
				j = fail[j];
			if(match(j, b + i - j))
				++j;
			fail[i + 1] = j;
		}
		ans = -1;
		for(int i = 0; i < n; ++i)
			fastIO::read(a[i]);
		for(int i = 0, j = 0; i < n; ++i) {
			while(j && !match(j, a + i - j))
				j = fail[j];
			if(match(j, a + i - j))
				++j;
			if(j == m) {
				ans = i - j + 1;
				break;
			}
		}
		if(ans == -1) {
			puts("no solution!");
		} else {
			printf("%d\n", ans);
		}
	}
	return 0;
}
