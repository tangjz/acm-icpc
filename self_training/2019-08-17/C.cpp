#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e6 + 1, maxc = 7, m1 = (int)1e9 + 7, m2 = (int)1e9 + 9;
const char *pat[maxc] = {"do", "re", "mi", "fa", "sol", "la", "si"};
int n, pL, pR, sta[maxn], ans[maxn + 2];
LL hh[maxn << 1 | 1], pw[maxn];
inline LL get_hash(int sta, int len) {
	int r11 = hh[sta - 1] >> 32, r12 = hh[sta - 1];
	int r21 = hh[sta + len - 1] >> 32, r22 = hh[sta + len - 1];
	int p1 = pw[len] >> 32, p2 = pw[len];
	r11 = (r21 - (LL)r11 * p1) % m1;
	r12 = (r22 - (LL)r12 * p2) % m2;
	return (LL)(r11 < 0 ? r11 + m1 : r11) << 32 | (r12 < 0 ? r12 + m2 : r12);
}
int main() {
	scanf("%d", &n);
	pL = pR = n + 1;
	for(int i = 1; i <= n; ++i) {
		char op1[3], op2[5];
		scanf("%s%s", op1, op2);
		for(int j = 0; j < 7; ++j) {
			if(strcmp(op2, pat[j]) != 0)
				continue;
			if(op1[0] == 'p') {
				hh[--pL] = j;
			} else {
				hh[pR++] = j;
			}
			break;
		}
		sta[i] = pL;
	}
	pw[0] = 1LL << 32 | 1;
	for(int i = pL; i < pR; ++i) {
		int ch = hh[i], r1 = hh[i - 1] >> 32, r2 = hh[i - 1];
		r1 = ((LL)r1 * maxc + ch) % m1;
		r2 = ((LL)r2 * maxc + ch) % m2;
		hh[i] = (LL)r1 << 32 | r2;
		r1 = pw[i - pL] >> 32;
		r2 = pw[i - pL];
		r1 = (LL)r1 * maxc % m1;
		r2 = (LL)r2 * maxc % m2;
		pw[i - pL + 1] = (LL)r1 << 32 | r2;
	}
	for(int i = 1; i <= n; ++i) {
		int L = i, R = n;
		while(L < R) {
			int M = (L + R + 1) >> 1;
			if(get_hash(sta[M], M - i) == get_hash(sta[M] + i, M - i)) {
				L = M;
			} else {
				R = M - 1;
			}
		}
		++ans[i];
		--ans[R + 1];
		ans[i] += ans[i - 1];
		printf("%d\n", ans[i]);
	}
	return 0;
}
