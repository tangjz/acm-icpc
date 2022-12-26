#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> Info;
const int maxn = 51, maxv = (int)1e5 + 5, maxp = 9593, maxc = 31, maxs = maxn * maxc;
const int BLEN = 13, maxi = 51, maxo = 399, maxd = (maxi - 1) / BLEN + 1, maxl = (maxo - 1) / BLEN + 1;
const LL BASE = (LL)1e13;
int tot, d[maxv], pr[maxp], mul[maxp][maxd | 1];
struct BigInt {
	int len;
	LL num[maxl];
	void read() {
		static char buf[(maxi + 1) | 1];
		scanf("%s", buf);
		int slen = strlen(buf);
		for(len = 0; slen > 0; slen -= BLEN, ++len) {
			num[len] = 0;
			for(int i = max(slen - BLEN, 0); i < slen; ++i)
				num[len] = num[len] * 10 + (buf[i] - '0');
		}
	}
	void write(char endc = '\n') const {
		printf("%lld", num[len - 1]);
		for(int i = len - 2; i >= 0; --i)
			printf("%0*lld", BLEN, num[i]);
		if(endc)
			putchar(endc);
	}
	void operator *= (int const &t) {
		LL rem = 0;
		for(int i = 0; i < len; ++i) {
			rem += num[i] * t;
			num[i] = rem % BASE;
			rem /= BASE;
		}
		if(rem)
			num[len++] = rem;
	}
	void operator /= (int const &t) {
		LL rem = 0;
		for(int i = len - 1; i >= 0; --i) {
			rem = rem * BASE + num[i];
			num[i] = rem / t;
			rem %= t;
		}
		if(len && !num[len - 1])
			--len;
	}
	LL dot(int const vec[]) {
		LL sum = 0;
		for(int i = 0; i < len; ++i)
			sum += num[i] * vec[i];
		return sum;
	}
} a[maxn * 3];
int t, n, q, ord[maxn * 3], deg[maxs], e[maxs][(maxc + 1) | 1];
Info ctr[maxs][maxs];
vector<Info> f[maxn * 3], lft, rht;
bool ban[maxn];
int main() {
	for(int i = 2; i < maxv; ++i) {
		if(!d[i]) {
			mul[tot][0] = 1;
			for(int j = 1; j < maxd; ++j)
				mul[tot][j] = mul[tot][j - 1] * BASE % i;
			pr[tot++] = d[i] = i;
		}
		for(int j = 0, k; (k = i * pr[j]) < maxv; ++j) {
			d[k] = pr[j];
			if(d[i] == pr[j])
				break;
		}
	}
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		for(int i = 0; i < n + n; ++i)
			a[i].read();
		scanf("%d", &q);
		for(int i = 0; i < q; ++i)
			a[n + n + i].read();
		vector<Info>().swap(lft);
		vector<Info>().swap(rht);
		for(int i = 0; i < n + n + q; ++i) {
			vector<Info>().swap(f[i]);
			ord[i] = i;
		}
		memset(ban, 0, q * sizeof(bool));
		for(int i = 0, cnt = n + n + q; i < tot && cnt > 0; ++i) {
			int ncnt = 0;
			for(int j = 0; j < cnt; ++j) {
				int o = ord[j];
				vector<Info> &ref = o < n + n && (o & 1) ? rht : lft;
				if(a[o].dot(mul[i]) % pr[i] > 0) {
					ord[ncnt++] = o;
					continue;
				}
				if(ref.empty() || ref.back().first != pr[i]) {
					if(o < n + n) {
						ref.push_back(make_pair(pr[i], 0));
					} else {
						ban[o - n - n] = 1;
						continue;
					}
				}
				if(o < n + n)
					++ref.back().second;
				f[o].push_back(make_pair(ref.size() - 1, 0));
				do {
					a[o] /= pr[i];
					++f[o].back().second;
				} while(a[o].dot(mul[i]) % pr[i] == 0);
				if(a[o].len > 1 || a[o].num[0] > 1)
					ord[ncnt++] = o;
			}
			cnt = ncnt;
		}
		int szL = lft.size(), szR = rht.size();
		memset(deg, 0, szR * sizeof(int));
		for(int i = 0; i < szL; ++i) {
			e[i][0] = 0;
			memset(ctr[i], 0, szR * sizeof(Info));
		}
		for(int i = 0; i < n; ++i) {
			vector<Info> &vL = f[i << 1], &vR = f[i << 1 | 1];
			for(vector<Info>::iterator it = vL.begin(); it != vL.end(); ++it)
				for(vector<Info>::iterator jt = vR.begin(); jt != vR.end(); ++jt) {
					if((jt -> second) % (it -> second) > 0)
						continue;
					int u = it -> first, v = jt -> first, pw = (jt -> second) / (it -> second);
					Info &cur = ctr[u][v];
					if(!cur.second) {
						cur.first = pw;
						e[u][++e[u][0]] = v;
						++deg[v];
					}
					if(cur.first == pw)
						++cur.second;
				}
		}
		for(int u = 0; u < szL; ++u) {
			int cnt = 0;
			for(int i = 1; i <= e[u][0]; ++i) {
				int v = e[u][i];
				if(ctr[u][v].second != lft[u].second || ctr[u][v].second != rht[v].second) {
					--deg[v];
				} else {
					e[u][++cnt] = v;
				}
			}
			e[u][0] = cnt;
		}
		bool bad = 0;
		for(int v = 0; !bad && v < szR; ++v)
			bad |= rht[v].second > 0 && !deg[v];
		for(int i = 0; i < q; ++i) {
			BigInt &cur = a[n + n + i];
			if(bad || ban[i] || cur.len > 1 || cur.num[0] > 1) {
				puts("NO");
				continue;
			}
			vector<Info> &vL = f[n + n + i];
			static Info g[maxs];
			memset(g, 0, szR * sizeof(Info));
			for(vector<Info>::iterator it = vL.begin(); it != vL.end(); ++it) {
				int u = it -> first, x = it -> second;
				for(int j = 1; j <= e[u][0]; ++j) {
					int v = e[u][j], y = x * ctr[u][v].first;
					if(!g[v].second)
						g[v].first = y;
					if(g[v].first == y)
						++g[v].second;
				}
			}
			for(int v = 0; !ban[i] && v < szR; ++v)
				ban[i] |= g[v].second > 0 && g[v].second != deg[v];
			if(ban[i]) {
				puts("NO");
			} else {
				printf("YES ");
				int prd = 1;
				for(int v = 0; v < szR; ++v) {
					if(!g[v].first)
						continue;
					int p = rht[v].first, upp = (maxv - 1) / p;
					for(int j = 0; j < g[v].first; ++j) {
						if(prd > upp) {
							cur *= prd;
							prd = 1;
						}
						prd *= p;
					}
				}
				if(prd > 1)
					cur *= prd;
				cur.write();
			}
		}
	}
	return 0;
}
