#include <bits/stdc++.h>
namespace fastIO {
	#define BUF_SIZE 1000001
	struct Ostream_fwrite {
		char *buf, *p1, *pend;
		Ostream_fwrite() { buf = new char[BUF_SIZE], p1 = buf, pend = buf + BUF_SIZE; }
		void out(char ch) {
			if(p1 == pend) fwrite(buf, 1, BUF_SIZE, stdout), p1 = buf;
			(*p1++) = ch;
		}
		void println(int x) {
			static char s[15], *s1;
			s1 = s, !x && ((*s1++) = '0'), x < 0 && (out('-'), x = -x);
			for( ; x; (*s1++) = x % 10 + '0', x /= 10);
			for( ; (s1--) != s; out(*s1)); out('\n');
		}
		~Ostream_fwrite() { if(p1 != buf) fwrite(buf, 1, p1 - buf, stdout), p1 = buf; }
	} Ostream;
	#undef BUF_SIZE
}
const int maxn = (int)1e6 + 1;
int n, m, p, q, fa[maxn], ans[maxn];
int find(int x) {
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}
int main() {
	scanf("%d%d%d%d", &n, &m, &p, &q);
	for(int i = 0; i <= n; ++i)
		fa[i] = i;
	for(int i = m, u = (i * p + q) % n, v = (i * q + p) % n; i > 0; --i, (u -= p) < 0 && (u += n), (v -= q) < 0 && (v += n)) {
		int l = u, r = v;
		if(l > r)
			std::swap(l, r);
		for(int j = find(l); j <= r; j = find(j)) {
			ans[j] = i;
			fa[j] = find(j + 1);
		}
	}
	for(int i = 0; i < n; ++i)
		fastIO::Ostream.println(ans[i]);
	return 0;
}