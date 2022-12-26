#include <stdio.h>
#include <cstring>
#include <unordered_map>
typedef long long LL;
const int maxn = 300001, maxd = 27, s1 = maxd, s2 = maxd, m1 = (int)1e9 + 7, m2 = (int)1e9 + 9;
int n, q, dsu[maxd], pw1[maxn], h1[maxn][maxd], pw2[maxn], h2[maxn][maxd];
char str[maxn];
std::unordered_map<int, int> sp1, sp2;
int dsu_find(int x) {
	return dsu[x] < 0 ? x : (dsu[x] = dsu_find(dsu[x]));
}
void dsu_merge(int u, int v) {
	u = dsu_find(u);
	v = dsu_find(v);
	if(u == v)
		return;
	if(dsu[u] < dsu[v])
		dsu[v] = u;
	else {
		if(dsu[u] == dsu[v])
			--dsu[v];
		dsu[u] = v;
	}
}
int main() {
	scanf("%s", str);
	n = strlen(str);
	pw1[0] = pw2[0] = 1;
	sp1[pw1[0]] = sp2[pw2[0]] = 0;
	for(int i = 1; i <= n; ++i) {
		pw1[i] = (LL)pw1[i - 1] * s1 % m1;
		pw2[i] = (LL)pw2[i - 1] * s2 % m2;
		sp1[pw1[i]] = sp2[pw2[i]] = i;
		for(int j = 1; j < maxd; ++j) {
			h1[i][j] = (LL)h1[i - 1][j] * s1 % m1;
			h2[i][j] = (LL)h2[i - 1][j] * s2 % m2;
		}
		int o = str[i - 1] - 'a' + 1;
		(++h1[i][o]) >= m1 && (h1[i][o] -= m1);
		(++h2[i][o]) >= m2 && (h2[i][o] -= m2);
	}
	scanf("%d", &q);
	while(q--) {
		int c, L1, R1, L2, R2;
		char op[3];
		scanf("%d%d%d%d%d", &c, &L1, &R1, &L2, &R2);
		--L1, --L2;
		if(R1 - L1 != R2 - L2) {
			while(c--)
				scanf("%*s");
			puts("NO");
			continue;
		}
		memset(dsu, -1, sizeof dsu);
		while(c--) {
			scanf("%s", op);
			dsu_merge(op[0] - 'a' + 1, op[1] - 'a' + 1);
		}
		int len = R1 - L1, seq[4][maxd] = {};
		for(int i = 1; i < maxd; ++i) {
			int j = dsu_find(i);
			(seq[0][j] -= h1[L1][i]) < 0 && (seq[0][j] += m1);
			(seq[0][j] += h1[L2][i]) >= m1 && (seq[0][j] -= m1);
			(seq[1][j] += h1[R1][i]) >= m1 && (seq[1][j] -= m1);
			(seq[1][j] -= h1[R2][i]) < 0 && (seq[1][j] += m1);
			(seq[2][j] -= h2[L1][i]) < 0 && (seq[2][j] += m2);
			(seq[2][j] += h2[L2][i]) >= m2 && (seq[2][j] -= m2);
			(seq[3][j] += h2[R1][i]) >= m2 && (seq[3][j] -= m2);
			(seq[3][j] -= h2[R2][i]) < 0 && (seq[3][j] += m2);
		}
		int df1, df2;
		c = 0;
		for(int i = 1; i < maxd; ++i) {
			if(i != dsu_find(i))
				continue;
			int dt1 = ((LL)seq[0][i] * pw1[len] + seq[1][i]) % m1;
			int dt2 = ((LL)seq[2][i] * pw2[len] + seq[3][i]) % m2;
			if(!dt1 && !dt2)
				continue;
			++c;
			if(c == 1) {
				df1 = dt1;
				df2 = dt2;
			} else {
				(dt1 += df1) >= m1 && (dt1 -= m1);
				(dt2 += df2) >= m2 && (dt2 -= m2);
				c += dt1 || dt2;
				if(c > 2)
					break;
			}
		}
		if(c == 0) {
			puts("YES");
		} else if(c == 2) {
			if(df1 && !sp1.count(df1)) {
				df1 = m1 - df1;
				if(df2)
					df2 = m2 - df2;
			}
			puts(sp1.count(df1) && sp2.count(df2) && sp1[df1] == sp2[df2] ? "YES" : "NO");
		} else {
			puts("NO");
		}
	}
	return 0;
}
