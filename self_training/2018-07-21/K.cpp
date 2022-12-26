#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxs = (int)1e6 + 1, mod1 = (int)1e9 + 7, mod2 = (int)1e9 + 9;
int n, m, p, q, nxt[maxs], seq1[maxs], seq2[maxs];
char buf[maxs];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0, idx = 0; i < n; ++i) {
		int h1 = 0, h2 = 0;
		scanf("%s", buf + idx);
		for(int j = 0; j < m; ++j, ++idx) {
			int o = buf[idx] - 'a';
			h1 = (29LL * h1 + o) % mod1;
			h2 = (29LL * h2 + o) % mod2;
		}
		seq1[i] = h1;
		seq2[i] = h2;
	}
	for(int i = 1, j = 0; i < n; ++i) {
		for( ; j && !(seq1[j] == seq1[i] && seq2[j] == seq2[i]); j = nxt[j]);
		nxt[i + 1] = seq1[j] == seq1[i] && seq2[j] == seq2[i] ? ++j : 0;
	}
	p = n - nxt[n];
	memset(seq1, 0, m * sizeof(int));
	memset(seq2, 0, m * sizeof(int));
	for(int i = 0, idx = 0; i < n; ++i)
		for(int j = 0; j < m; ++j, ++idx) {
			int o = buf[idx] - 'a';
			seq1[j] = (29LL * seq1[j] + o) % mod1;
			seq2[j] = (29LL * seq2[j] + o) % mod2;
		}
	for(int i = 1, j = 0; i < m; ++i) {
		for( ; j && !(seq1[j] == seq1[i] && seq2[j] == seq2[i]); j = nxt[j]);
		nxt[i + 1] = seq1[j] == seq1[i] && seq2[j] == seq2[i] ? ++j : 0;
	}
	q = m - nxt[m];
	for(int i = 0, idx = 0; i < n; ++i) {
		int *seq = seq1, *res = seq2;
		int *que = nxt, L = 0, R = 0;
		for(int j = 0; j < m; ++j, ++idx) {
			scanf("%d", seq + j);
			for( ; L < R && j - que[L] >= q; ++L);
			for( ; L < R && seq[j] >= seq[que[R - 1]]; --R);
			que[R++] = j;
			res[idx] = seq[que[L]];
//			printf("%d%c", res[idx], " \n"[j == m - 1]);
		}
	}
	int ans = ~0u >> 1;
	for(int j = q - 1; j < m; ++j) {
		int *seq = seq1, *res = seq2;
		int *que = nxt, L = 0, R = 0;
		for(int i = 0, idx = j; i < n; ++i, idx += m) {
			seq[i] = res[idx];
//			printf("%d%c", seq[i], " \n"[i == n - 1]);
		}
		for(int i = 0; i < n; ++i) {
			for( ; L < R && i - que[L] >= p; ++L);
			for( ; L < R && seq[i] >= seq[que[R - 1]]; --R);
			que[R++] = i;
			i >= p - 1 && (ans = min(ans, seq[que[L]]));
//			printf("%d%c", seq[que[L]], " \n"[i == n - 1]);
		}
	}
//	printf("%d %d %d\n", ans, p, q);
	printf("%lld\n", ans * (p + 1LL) * (q + 1)); 
	return 0;
}
