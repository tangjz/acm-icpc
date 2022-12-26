#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int s[9][9], t[9][9], row[9], col[9], perm[11][19];
bool dfs(int idx) {
	if(idx == 9)
		return 1;
	int *cur = perm[idx], *nxt = perm[idx + 1];
	int bx = idx / 3, by = idx % 3;
	int dx = bx * 3, dy = by * 3, xL, xR, yL, yR;
	if(by) {
		xL = xR = 0;
	} else {
		xL = dx;
		xR = xL + 3;
		for(int i = xL; i < xR; ++i)
			row[i] = i;
	}
	do {
		if(bx) {
			yL = yR = 0;
		} else {
			yL = dy;
			yR = yL + 3;
			for(int i = yL; i < yR; ++i)
				col[i] = i;
		}
		do {
			bool chk = 1;
			memcpy(nxt, cur, sizeof perm[0]);
			for(int i = 0; chk && i < 3; ++i)
				for(int j = 0; chk && j < 3; ++j) {
					int u = s[row[dx + i]][col[dy + j]];
					int v = t[dx + i][dy + j];
					if(v == -1)
						continue;
					if(nxt[u] == -1) {
						nxt[u] = v;
					} else {
						chk &= nxt[u] == v;
					}
					if(nxt[9 + v] == -1) {
						nxt[9 + v] = u;
					} else {
						chk &= nxt[9 + v] == u;
					}
				}
			if(!chk)
				continue;
			if(dfs(idx + 1))
				return 1;
		} while(next_permutation(col + yL, col + yR));
	} while(next_permutation(row + xL, row + xR));
	return 0;
}
bool check() {
	int mat[9][9], row[3], col[3];
	memcpy(mat, s, sizeof mat);
	for(int i = 0; i < 3; ++i)
		row[i] = col[i] = i;
	memset(perm[0], -1, sizeof perm[0]);
	do {
		do {
			for(int i = 0; i < 9; ++i)
				for(int j = 0; j < 9; ++j)
					s[i][j] = mat[3 * row[i / 3] + i % 3][3 * col[j / 3] + j % 3];
			if(dfs(0))
				return 1;
		} while(next_permutation(col, col + 3));
	} while(next_permutation(row, row + 3));
	return 0;
}
int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		for(int i = 0; i < 9; ++i)
			for(int j = 0; j < 9; ++j) {
				scanf("%1d", s[i] + j);
				--s[i][j];
			}
		for(int i = 0; i < 9; ++i)
			for(int j = 0; j < 9; ++j) {
				scanf("%1d", t[i] + j);
				--t[i][j];
			}
		if(check()) {
			puts("Yes");
		} else {
			for(int i = 0; i < 9; ++i)
				for(int j = i + 1; j < 9; ++j)
					swap(s[i][j], s[j][i]);
			puts(check() ? "Yes" : "No");
		}
	}
	return 0;
}
