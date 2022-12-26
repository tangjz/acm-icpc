#include <cstdio>
typedef long long LL;
const int maxn = 501, s1 = 29, s2 = 425149, m1 = (int)1e9 + 7, m2 = (int)1e9 + 9, maxs = 1 << 18;
int n, m, tot, st, tim[maxs | 1], lnk[maxs | 1];
struct Pair {
	int v1, v2;
	Pair operator - (Pair const &t) const {
		int r1 = v1 - t.v1, r2 = v2 - t.v2;
		return (Pair){r1 < 0 ? r1 + m1 : r1, r2 < 0 ? r2 + m2 : r2};
	}
	Pair operator + (Pair const &t) const {
		int r1 = v1 + t.v1, r2 = v2 + t.v2;
		return (Pair){r1 < m1 ? r1 : r1 - m1, r2 < m2 ? r2 : r2 - m2};
	}
	Pair operator + (int const &t) const {
		int r1 = v1 + t, r2 = v2 + t;
		return (Pair){r1 < m1 ? r1 : r1 - m1, r2 < m2 ? r2 : r2 - m2};
	}
	Pair operator * (Pair const &t) const {
		return (Pair){(int)((LL)v1 * t.v1 % m1), (int)((LL)v2 * t.v2 % m2)};
	}
	Pair operator * (int const &t) const {
		return (Pair){(int)((LL)v1 * t % m1), (int)((LL)v2 * t % m2)};
	}
} pw1[maxn], pw2[maxn], h[maxn][maxn];
struct Edge {
	int nxt;
	LL val;
} e[maxn * maxn];
char buf[maxn][maxn + 2];
bool check(LL val) {
	int pos = val & (maxs - 1);
	if(tim[pos] != st) {
		tim[pos] = st;
		lnk[pos] = -1;
	}
	for(int it = lnk[pos]; it != -1; it = e[it].nxt)
		if(e[it].val == val)
			return 1;
	e[tot] = (Edge){lnk[pos], val};
	lnk[pos] = tot++;
	return 0;
}
int main() {
	pw1[0] = pw2[0] = (Pair){1, 1};
	for(int i = 1; i < maxn; ++i) {
		pw1[i] = pw1[i - 1] * s1;
		pw2[i] = pw2[i - 1] * s2;
	}
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", buf[i] + 1);
		for(int j = 1; j <= m; ++j)
			h[i][j] = h[i][j - 1] * s1 + (buf[i][j] - 'a');
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j)
			h[i][j] = h[i - 1][j] * s2 + h[i][j];
	for(int len = n < m ? n : m; len > 0; --len) {
		tot = 0;
		++st;
		Pair sx = pw1[len], sy = pw2[len], sz = sx * sy;
		for(int i = len; i <= n; ++i)
			for(int j = len; j <= m; ++j) {
				Pair val = h[i][j] - h[i][j - len] * sx - h[i - len][j] * sy + h[i - len][j - len] * sz;
				if(check((LL)val.v1 << 32 | val.v2)) {
					printf("%d\n", len);
					return 0;
				}
			}
	}
	puts("0");
	return 0;
}
