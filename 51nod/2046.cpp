#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
using namespace std;
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
		void println(int x) {
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
			out('\n');
		}
		void println(char *s) {
			for(char *s1 = s; *s1; out(*s1++));
			out('\n');
		}
		~Output() {
			if(p1 != buf) {
				fwrite(buf, 1, p1 - buf, stdout);
				p1 = buf;
			}
		}
	} Ostream;
	inline void println(int x) {
		Ostream.println(x);
	}
	inline void println(char *s) {
		Ostream.println(s);
	}
	#undef BUF_SIZE
};
const int maxn = (int)1e5 + 1, maxs = 500, maxm = 201, INF = 0x3f3f3f3f;
int n, m, seq[maxn], idx[maxn], dsu[maxn], Ref[maxn], f[maxm][maxn];
vector<int> pos[maxn], pool, que;
inline void upd(int &x, int y) {
	x > y && (x = y);
}
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void build(int u, int dis[]) {
	memset(dis, 0x3f, sizeof f[0]);
	for(int i = 0, j = -1; i < n; ++i) {
		int v = dsu_find(seq[i]);
		if(u == v)
			j = i;
		else if(j != -1)
			upd(dis[v], i - j);
	}
	for(int i = n - 1, j = -1; i >= 0; --i) {
		int v = dsu_find(seq[i]);
		if(u == v)
			j = i;
		else if(j != -1)
			upd(dis[v], j - i);
	}
}
int main() {
	fastIO::read(n), fastIO::read(m);
	for(int i = 0; i < maxn; ++i) {
		dsu[i] = Ref[i] = -1;
		idx[i] = i;
	}
	for(int i = 0; i < maxm; ++i)
		pool.push_back(i);
	for(int i = 0; i < n; ++i) {
		fastIO::read(seq[i]);
		pos[seq[i]].push_back(i);
	}
	for(int i = 0; i < maxn; ++i)
		if((int)pos[i].size() >= maxs) {
			int o = Ref[i] = pool.back();
			pool.pop_back();
			build(i, f[o]);
			vector<int>().swap(pos[i]);
			que.push_back(o);
		} else if(!pos[i].size())
			idx[i] = -1;
	int ans = 0;
	while(m--) {
		int typ, x, y;
		fastIO::read(typ), fastIO::read(x), fastIO::read(y);
		x ^= ans;
		y ^= ans;
		if(typ == 1) {
			if(x == y)
				continue;
			int u = x < maxn ? idx[x] : -1;
			int v = y < maxn ? idx[y] : -1;
			if(u == -1)
				continue;
			if(v == -1) {
				idx[x] = -1;
				idx[y] = u;
				continue;
			}
			if((int)pos[u].size() + (Ref[u] != -1 ? maxs : 0) > (int)pos[v].size() + (Ref[v] != -1 ? maxs : 0))
				swap(u, v);
			idx[x] = -1;
			idx[y] = v;
			dsu[u] = v;
			if(Ref[u] != -1 && Ref[v] != -1) {
				remove(que.begin(), que.end(), Ref[u]);
				que.pop_back();
				pool.push_back(Ref[u]);
				Ref[u] = -1;
				build(v, f[Ref[v]]);
				vector<int>().swap(pos[u]);
				vector<int>().swap(pos[v]);
			} else if((int)pos[u].size() + (int)pos[v].size() >= maxs) {
				int &o = Ref[v];
				if(o == -1) {
					o = pool.back();
					pool.pop_back();
					que.push_back(o);
				}
				build(v, f[o]);
				vector<int>().swap(pos[u]);
				vector<int>().swap(pos[v]);
			} else {
				vector<int> seq;
				for(vector<int>::iterator it = pos[u].begin(), jt = pos[v].begin(); it != pos[u].end() || jt != pos[v].end(); )
					if(jt == pos[v].end() || (it != pos[u].end() && *it < *jt))
						seq.push_back(*(it++));
					else
						seq.push_back(*(jt++));
				vector<int>().swap(pos[u]);
				seq.swap(pos[v]);
			}
			for(vector<int>::iterator it = que.begin(); it != que.end(); ++it)
				if(*it != Ref[u] && *it != Ref[v]) {
					int o = *it;
					upd(f[o][v], f[o][u]);
				}
		} else {
			int u = x < maxn ? idx[x] : -1;
			int v = y < maxn ? idx[y] : -1;
			if(u == -1 || v == -1) {
				ans = 0;
				fastIO::println("Chtholly");
				continue;
			}
			if(u == v) {
				fastIO::println(ans = 0);
				continue;
			}
			ans = INF;
			if(Ref[u] != -1)
				upd(ans, f[Ref[u]][v]);
			if(Ref[v] != -1)
				upd(ans, f[Ref[v]][u]);
			if(pos[u].size() && pos[v].size()) {
				int i = -1, j = -1;
				for(vector<int>::iterator it = pos[u].begin(), jt = pos[v].begin(); it != pos[u].end() || jt != pos[v].end(); )
					if(jt == pos[v].end() || (it != pos[u].end() && *it < *jt)) {
						i = *(it++);
						if(j != -1)
							upd(ans, i - j);
					} else {
						j = *(jt++);
						if(i != -1)
							upd(ans, j - i);
					}
			}
			fastIO::println(ans);
		}
	}
	return 0;
}
