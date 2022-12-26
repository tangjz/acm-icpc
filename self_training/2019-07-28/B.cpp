#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 9;
int t, n, m, dt, typ[maxn], fir[maxn], las[maxn], ord[2][maxn], tim[maxn], ans[maxn];
inline bool cmp(int const &u, int const &v) {
	return las[u] < las[v];
}
int main() {
	scanf("%d", &t);
	for(int Case = 1; Case <= t; ++Case) {
		scanf("%d%d%d", &n, &m, &dt);
		ord[0][0] = ord[1][0] = 0;
		for(int i = 1; i <= m; ++i) {
			char op;
			scanf("%d %c", fir + i, &op);
			typ[i] = op == 'C';
			las[i] = (fir[i] + (typ[i] ? dt : -dt) - 1) % n + 1;
			if(las[i] <= 0)
				las[i] += n;
			ord[typ[i]][++ord[typ[i]][0]] = i;
		}
		sort(ord[0] + 1, ord[0] + ord[0][0] + 1, cmp);
		sort(ord[1] + 1, ord[1] + ord[1][0] + 1, cmp);
		memset(tim + 1, 0, n * sizeof(int));
		++dt;
		for(int i = 1, j; i <= ord[0][0]; i = j) {
			for(j = i + 1; j <= ord[0][0] && fir[ord[0][i]] == fir[ord[0][j]]; ++j);
			int sta = las[ord[0][i]], len = (j <= ord[0][0] ? las[ord[0][j]] : las[ord[0][1]]) - sta;
			if(len <= 0)
				len += n;
			len = min(len, dt);
			for(int k = 0, pos = sta; k < len; ++k, (++pos) > n && (pos = 1))
				tim[pos] = max(tim[pos], dt - k);
		}
		for(int i = 1, j; i <= ord[1][0]; i = j) {
			for(j = i + 1; j <= ord[1][0] && fir[ord[1][i]] == fir[ord[1][j]]; ++j);
			int sta = las[ord[1][i]], len = sta - (i > 1 ? las[ord[1][i - 1]] : las[ord[1][ord[1][0]]]);
			if(len <= 0)
				len += n;
			len = min(len, dt);
			for(int k = 0, pos = sta; k < len; ++k, (--pos) < 1 && (pos = n))
				tim[pos] = max(tim[pos], dt - k);
		}
		for(int i = 1, j; i <= ord[0][0]; i = j) {
			for(j = i + 1; j <= ord[0][0] && fir[ord[0][i]] == fir[ord[0][j]]; ++j);
			int sta = las[ord[0][i]], len = (j <= ord[0][0] ? las[ord[0][j]] : las[ord[0][1]]) - sta;
			if(len <= 0)
				len += n;
			len = min(len, dt);
			int cnt = 0;
			for(int k = 0, pos = sta; k < len; ++k, (++pos) > n && (pos = 1))
				cnt += tim[pos] == dt - k;
			for(int k = i; k < j; ++k)
				ans[ord[0][k]] = cnt;
		}
		for(int i = 1, j; i <= ord[1][0]; i = j) {
			for(j = i + 1; j <= ord[1][0] && fir[ord[1][i]] == fir[ord[1][j]]; ++j);
			int sta = las[ord[1][i]], len = sta - (i > 1 ? las[ord[1][i - 1]] : las[ord[1][ord[1][0]]]);
			if(len <= 0)
				len += n;
			len = min(len, dt);
			int cnt = 0;
			for(int k = 0, pos = sta; k < len; ++k, (--pos) < 1 && (pos = n))
				cnt += tim[pos] == dt - k;
			for(int k = i; k < j; ++k)
				ans[ord[1][k]] = cnt;
		}
		printf("Case #%d:", Case);
		for(int i = 1; i <= m; ++i)
			printf(" %d", ans[i]);
		printf("\n");
	}
	return 0;
}
