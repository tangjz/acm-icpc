#include <bits/stdc++.h>
using namespace std;
const int maxn = 101;
int n, seq[maxn << 1 | 1][maxn], idx[maxn * maxn], mat[maxn][maxn];
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n << 1; ++i) {
		for(int j = 1; j <= n; ++j)
			scanf("%d", seq[i] + j);
		if(idx[seq[i][1]]) {
			for(int j = 1; j <= n; ++j)
				mat[1][j] = seq[i][j];
		} else {
			idx[seq[i][1]] = i;
		}
	}
	for(int i = 1; i <= n; ++i) {
		int j = idx[mat[1][i]];
		for(int k = 2; k <= n; ++k)
			mat[k][i] = seq[j][k];
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j)
			printf("%d%c", mat[i][j], " \n"[i == n && j == n]);
	return 0;
}
