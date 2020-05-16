#include <bits/stdc++.h>
const int maxn = 31, maxt = (int)1e7, DELTA = (int)1e3;
int n, m;
char buf[maxn][maxn];
inline void remove(int x, int y) {
	switch(buf[x][y]) {
		case 'L': buf[x][y] = buf[x][y + 1] = '.'; break;
		case 'R': buf[x][y] = buf[x][y - 1] = '.'; break;
		case 'T': buf[x][y] = buf[x + 1][y] = '.'; break;
		case 'B': buf[x][y] = buf[x - 1][y] = '.';
	}
}
inline void random_walk() {
	if(rand() & 1) { // L, R
		int x = rand() % n, y = rand() % (n - 1);
		if(buf[x][y] == 'L' && buf[x][y + 1] == 'R') {
			buf[x][y] = buf[x][y + 1] = '.';
		} else if(buf[x][y] == '.' && buf[x][y + 1] == '.') {
			buf[x][y] = 'L';
			buf[x][y + 1] = 'R';
		}
	} else { // T, B
		int x = rand() % (n - 1), y = rand() % n;
		if(buf[x][y] == 'T' && buf[x + 1][y] == 'B') {
			buf[x][y] = buf[x + 1][y] = '.';
		} else if(buf[x][y] == '.' && buf[x + 1][y] == '.') {
			buf[x][y] = 'T';
			buf[x + 1][y] = 'B';
		}
	}
}
int main() {
	freopen("domino.in", "r", stdin);
	freopen("domino.out", "w", stdout);
	scanf("%d%d", &n, &m);
	srand(time(0));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			buf[i][j] = '.';
	for(int i = 0; i < maxt; ++i)
		random_walk();
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j)
			puts(buf[j]);
		if(i == m - 1)
			break;
		puts("");
		for(int j = 0; j < DELTA; ++j)
			random_walk();
	}
	return 0;
}
