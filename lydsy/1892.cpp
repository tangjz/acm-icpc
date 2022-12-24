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
	struct Ostream_fwrite {
		char *buf, *p1, *pend;
		Ostream_fwrite() { buf = new char[BUF_SIZE], p1 = buf, pend = buf + BUF_SIZE; }
		void out(char ch) {
			if(p1 == pend) fwrite(buf, 1, BUF_SIZE, stdout), p1 = buf;
			(*p1++) = ch;
		}
		void write(int x, char endc = '\0') {
			static char s[15], *s1;
			s1 = s, !x && ((*s1++) = '0'), x < 0 && (out('-'), x = -x);
			for( ; x; (*s1++) = x % 10 + '0', x /= 10);
			for( ; (s1--) != s; out(*s1)); if(endc) out(endc);
		}
		~Ostream_fwrite() { if(p1 != buf) fwrite(buf, 1, p1 - buf, stdout), p1 = buf; }
	} Ostream;
	#undef BUF_SIZE
}
const int maxn = (int)5e5 + 1, maxv = (int)1e4 + 1;
int n, m, upp, a[maxn], b[maxn], les[maxn], eq[maxn], gre[maxn], fail[maxn], cnt, ans[maxn];
int pos[maxv + 2], pL[maxv + 2], pR[maxv + 2];
inline bool match(int pos, int *txt) {
	return (les[pos] == -1 || txt[les[pos]] < txt[pos])
		&& (eq[pos] == -1 || txt[eq[pos]] == txt[pos])
		&& (gre[pos] == -1 || txt[gre[pos]] > txt[pos]);
}
int main() {
	fastIO::read(n), fastIO::read(m), fastIO::read(upp);
	for(int i = 0; i < n; ++i)
		fastIO::read(a[i]);
	memset(pos, -1, (upp + 2) * sizeof(int));
	for(int i = 0; i < m; ++i) {
		int &x = b[i];
		fastIO::read(x);
		eq[i] = pos[x];
		pos[x] = i;
	}
	int las = 0;
	for(int i = 1; i <= upp; ++i)
		if(pos[i] != -1) {
			pL[i] = las;
			pR[las] = i;
			las = i;
		}
	pL[upp + 1] = las;
	pR[las] = upp + 1;
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
	for(int i = 0, j = 0; i < n; ++i) {
		while(j && !match(j, a + i - j))
			j = fail[j];
		if(match(j, a + i - j))
			++j;
		if(j == m) {
			ans[cnt++] = i - j + 1;
			j = fail[j];
		}
	}
	fastIO::Ostream.write(cnt, '\n');
	for(int i = 0; i < cnt; ++i)
		fastIO::Ostream.write(ans[i] + 1, " \n"[i == cnt - 1]);
	return 0;
}