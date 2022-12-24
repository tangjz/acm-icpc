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
const int maxn = (int)1e6 + 3;
int n, m, a[maxn], b[maxn], pL[maxn], pR[maxn], dL[maxn], dR[maxn], fail[maxn], cnt, ans[maxn];
int main() {
	fastIO::read(m), fastIO::read(n);
	for(int i = 0, x; i < m; ++i) {
		fastIO::read(a[i]);
		b[--a[i]] = i;
		pL[i] = i - 1;
		pR[i] = i + 1;
	}
	int sta = m + 1, end = m;
	pL[0] = sta;
	pR[sta] = 0;
	pL[end] = m - 1;
	pR[m - 1] = end;
	a[sta] = a[end] = -1;
	for(int i = m - 1; i >= 0; --i) {
		int x = b[i];
		dL[i] = a[pL[x]] == -1 ? -1 : i - a[pL[x]];
		dR[i] = a[pR[x]] == -1 ? -1 : i - a[pR[x]];
		pL[pR[x]] = pL[x];
		pR[pL[x]] = pR[x];
	}
	for(int i = 1, j = 0; i < m; ++i) {
		while(j && !((dL[j] == -1 || b[i - dL[j]] < b[i]) && (dR[j] == -1 || b[i] < b[i - dR[j]])))
			j = fail[j];
		if((dL[j] == -1 || b[i - dL[j]] < b[i]) && (dR[j] == -1 || b[i] < b[i - dR[j]]))
			++j;
		fail[i + 1] = j;
	}
	for(int i = 0, j = 0; i < n; ++i) {
		fastIO::read(a[i]);
		while(j && !((dL[j] == -1 || a[i - dL[j]] < a[i]) && (dR[j] == -1 || a[i] < a[i - dR[j]])))
			j = fail[j];
		if((dL[j] == -1 || a[i - dL[j]] < a[i]) && (dR[j] == -1 || a[i] < a[i - dR[j]]))
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