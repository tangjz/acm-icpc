#include <bits/stdc++.h>
using namespace std;
const int maxn = 3001;
int n, m, a, b;
char buf[maxn][maxn];
int main() {
	scanf("%d%d%d%d", &n, &m, &a, &b);
	int row = n & 1 ? m >> 1 : 0, col = m & 1 ? n >> 1 : 0, sp = n & 1 && m & 1;
	int aa = max(a - row, 0), bb = max(b - col, 0);
	int com = (aa >> 1) + (bb >> 1), spa = aa & 1, spb = bb & 1;
	int upp = (n >> 1) * (m >> 1);
	if(com + spa + spb <= upp) {
		for(int i = 0; i < a && i < row; ++i) {
			buf[0][i << 1] = '<';
			buf[0][i << 1 | 1] = '>';
		}
		for(int i = 0; i < b && i < col; ++i) {
			buf[(n & 1) + (i << 1)][0] = '^';
			buf[(n & 1) + (i << 1 | 1)][0] = 'v';
		}
	} else if(sp && com + 1 <= upp) {
		if(spa) {
			for(int i = 0; i < b && i < col; ++i) {
				buf[(i << 1)][0] = '^';
				buf[(i << 1 | 1)][0] = 'v';
			}
			for(int i = 0; i < a && i < row; ++i) {
				buf[0][(m & 1) + (i << 1)] = '<';
				buf[0][(m & 1) + (i << 1 | 1)] = '>';
			}
			buf[n - 1][0] = '<';
			buf[n - 1][1] = '>';
			--aa;
			if(spb) {
				buf[n - 2][2] = '^';
				buf[n - 1][2] = 'v';
				--bb;
			}
		} else {
			for(int i = 0; i < a && i < row; ++i) {
				buf[0][i << 1] = '<';
				buf[0][i << 1 | 1] = '>';
			}
			for(int i = 0; i < b && i < col; ++i) {
				buf[(n & 1) + (i << 1)][0] = '^';
				buf[(n & 1) + (i << 1 | 1)][0] = 'v';
			}
			buf[0][m - 1] = '^';
			buf[1][m - 1] = 'v';
			--bb;
		}
	} else {
		puts("NO");
		return 0;
	}
	for(int i = 0; i < n >> 1 && aa + bb; ++i)
		for(int j = 0; j < m >> 1 && aa + bb; ++j) {
			if(aa && !buf[(n & 1) + (i << 1)][(m & 1) + (j << 1)] && !buf[(n & 1) + (i << 1)][(m & 1) + (j << 1 | 1)]) {
				buf[(n & 1) + (i << 1)][(m & 1) + (j << 1)] = '<';
				buf[(n & 1) + (i << 1)][(m & 1) + (j << 1 | 1)] = '>';
				--aa;
			}
			if(aa && !buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1)] && !buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1 | 1)]) {
				buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1)] = '<';
				buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1 | 1)] = '>';
				--aa;
			}
			if(bb && !buf[(n & 1) + (i << 1)][(m & 1) + (j << 1)] && !buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1)]) {
				buf[(n & 1) + (i << 1)][(m & 1) + (j << 1)] = '^';
				buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1)] = 'v';
				--bb;
			}
			if(bb && !buf[(n & 1) + (i << 1)][(m & 1) + (j << 1 | 1)] && !buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1 | 1)]) {
				buf[(n & 1) + (i << 1)][(m & 1) + (j << 1 | 1)] = '^';
				buf[(n & 1) + (i << 1 | 1)][(m & 1) + (j << 1 | 1)] = 'v';
				--bb;
			}
		}
	assert(!aa && !bb);
	puts("YES");
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j)
			if(!buf[i][j])
				buf[i][j] = '.';
		buf[i][m] = '\0';
		puts(buf[i]);
	}
	return 0;
}
