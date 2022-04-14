#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, p[maxn], lft[maxn], rht[maxn];
char buf[maxn];
int main() {
	scanf("%d%d%s", &n, &m, buf);
	for(int i = 0, las[2] = {-1, -1}; i < n; ++i) {
		int o = buf[i] - '0';
		lft[i] = las[o ^ 1];
		las[o] = i;
	}
	for(int i = n - 1, las[2] = {n, n}; i >= 0; --i) {
		int o = buf[i] - '0';
		rht[i] = las[o ^ 1];
		las[o] = i;
	}
	bool fir = 0, sec = 1;
	for(char op = '0'; op <= '1' && !fir; ++op) {
		int sz = 0;
		for(int i = 0; i < n; ++i)
			if(buf[i] != op)
				p[sz++] = i;
		for(int L = 0, R = m - 1, pL = 0, pR = -1; R < n; ++L, ++R) {
			for( ; pL < sz && p[pL] < L; ++pL);
			for( ; pR + 1 < sz && p[pR + 1] <= R; ++pR);
			if(pL == 0 && pR == sz - 1) {
				fir = 1;
				break;
			}
			int uL = p[pL ? 0 : pR + 1];
			int uR = p[pR < sz - 1 ? sz - 1 : pL - 1];
			int vL = uL > 0 ? 0 : min(rht[uL], uR + 1);
			int vR = uR < n - 1 ? n - 1 : max(lft[uR], uL - 1);
			sec &= uR - uL + 1 <= m || vR - vL + 1 <= m;
		}
	}
	puts(fir ? "tokitsukaze" : (sec ? "quailty" : "once again"));
	return 0;
}