#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = 2001, dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};
int r, c, x, y;
LL n;
char buf[maxn][maxn];
int main() {
	scanf("%d%d%d%d%lld", &r, &c, &x, &y, &n);
	x = (x - 1 + n / 4 * 2) % r;
	y = (y - 1 - n / 4 * 2) % c;
	for(LL i = n / 4 * 4 + 1, o = 0; i <= n; ++i, ++o) {
		x = (x + i * dx[o]) % r;
		y = (y + i * dy[o]) % c;
	}
	x < 0 && (x += r);
	y < 0 && (y += c);
	buf[x][y] = '@';
	for(int i = 0, mx = (r + c) * 2; i < n && i < mx; ++i) {
		LL j = n - i;
		int o = (j - 1) & 3, step = (dx[o] ? r : 0) + (dy[o] ? c : 0);
		char ch = 'A' + (j - 1) % 26;
		if(step > j)
			step = j;
		for(int k = 0, xx = x, yy = y; k < step; ++k) {
			(xx -= dx[o]) < 0 && (xx += r) || xx >= r && (xx -= r);
			(yy -= dy[o]) < 0 && (yy += c) || yy >= c && (yy -= c);
			if(!buf[xx][yy])
				buf[xx][yy] = ch;
		}
		(x = (x - j * dx[o]) % r) < 0 && (x += r);
		(y = (y - j * dy[o]) % c) < 0 && (y += c); 
	}
	for(int i = 0; i < r; ++i) {
		for(int j = 0; j < c; ++j)
			if(!buf[i][j])
				buf[i][j] = '.';
		buf[i][c] = '\0';
		puts(buf[i]);
	}
	return 0;
}
