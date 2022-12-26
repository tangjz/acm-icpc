#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e6 + 1;
int tot, pr[maxn >> 3 | 1], d[maxn];
int n, a[maxn], b[maxn], pos[maxn], val[maxn];
namespace fastIO {
	#define BUF_SIZE (1 << 20 | 1)
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror)
			return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	//fwrite -> write
	struct Output {
		char buf[BUF_SIZE], *p1, *pend;
		Output() : p1(buf), pend(buf + BUF_SIZE) {}
		void out(char ch) {
			if(p1 == pend) {
				fwrite(buf, 1, BUF_SIZE, stdout);
				p1 = buf;
			}
			*p1++ = ch;
		}
		void print(const char s[]) {
			for(char *s1 = (char *)s; *s1; out(*s1++));
		}
		void print(int x) {
			static char s[13], *s1;
			s1 = s;
			if(!x)
				*s1++ = '0';
			if(x < 0) {
				out('-');
				x = -x;
			}
			for( ; x; *s1++ = x % 10 + '0', x /= 10);
			for( ; s1-- != s; out(*s1));
		}
		~Output() {
			if(p1 != buf) {
				fwrite(buf, 1, p1 - buf, stdout);
				p1 = buf;
			}
		}
	} Ostream;
	template<class T>
	inline void print(T x, char endc = '\0') {
		Ostream.print(x);
		if(endc != '\0')
			Ostream.out(endc);
	}
	#undef BUF_SIZE
};
int main() {
	for(int i = 2; i < maxn; ++i) {
		if(!d[i])
			pr[tot++] = d[i] = i;
		for(int j = 0, k; (k = i * pr[j]) < maxn; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	while(fastIO::read(n), !fastIO::IOerror) {
		for(int i = 1; i <= n; ++i) {
			fastIO::read(a[i]);
			val[i] = pos[i] = -1;
		}
		for(int i = 1; i <= n; ++i)
			fastIO::read(b[i]);
		bool chk = 1;
		for(int i = 1; i <= n; ++i) {
			if(pos[i] != -1)
				continue;
			int cnt = 0, sft = -1;
			for(int j = i; pos[j] == -1; j = a[j])
				pos[j] = cnt++;
			for(int j = i, k = 0; k < cnt; j = a[j], ++k) {
				if(pos[b[j]] < 0) {
					chk = 0;
					break;
				}
				int tmp = pos[j] - pos[b[j]];
				tmp < 0 && (tmp += cnt);
				if(sft == -1) {
					sft = tmp;
				} else if(sft != tmp) {
					chk = 0;
					break;
				}
			}
			for(int j = i, k = 0; k < cnt; j = a[j], ++k)
				pos[j] = -2;
			while(chk && cnt > 1) {
				int pp = d[cnt], cc = 0;
				for( ; d[cnt] == pp; ++cc, cnt /= pp);
				for(int i = 0, pw = 1; i < cc; ++i) {
					pw *= pp;
					int rem = sft % pw;
					if(val[pw] == -1) {
						val[pw] = rem;
					} else if(val[pw] != rem) {
						chk = 0;
						break;
					}
				}
			}
			if(!chk)
				break;
		}
		fastIO::print(chk ? "Ever" : "Forever", '\n');
	}
	return 0;
}
