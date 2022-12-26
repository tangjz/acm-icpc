#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)4e4 + 1;
int f[maxn], c[maxn], n, m;
int solve(int x, int y) {
	int ret = 0;
	for(int p = 0, q = 1; q <= n; ++q) {
		for( ; p * y <= x * q; ++p);
		c[q] = c[q - 1] + p - 1;
	}
	for(int i = 0, j, k; i < n; i = j) {
		k = n / (i + 1);
		j = n / k;
		ret += (f[j] - f[i]) * c[k];
	}
	return ret;
}
int main() {
	scanf("%d%d", &n, &m);
	f[1] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = i + i; j <= n; j += i)
			f[j] -= f[i];
		f[i] += f[i - 1];
	}
	int xL = 0, yL = 1, xM, yM, xR = 1, yR = 1;
	while(xM = xL + xR, yM = yL + yR, yM <= n)
		if(solve(xM, yM) < m) {
			int pL = 1, pM, pR = (n - yL) / yR;
			while(pL < pR) {
				pM = (pL + pR + 1) >> 1;
				xM = xL + pM * xR;
				yM = yL + pM * yR;
				if(solve(xM, yM) < m) {
					pL = pM;
				} else {
					pR = pM - 1;
				}
			}
			xL += pL * xR;
			yL += pL * yR;
		} else {
			int pL = 1, pM, pR = (n - yR) / yL;
			while(pL < pR) {
				pM = (pL + pR + 1) >> 1;
				xM = xR + pM * xL;
				yM = yR + pM * yL;
				if(solve(xM, yM) >= m) {
					pL = pM;
				} else {
					pR = pM - 1;
				}
			}
			xR += pL * xL;
			yR += pL * yL;
		}
	printf("%d %d\n", xR, yR);
	return 0;
}
