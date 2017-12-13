#include <cstdio>
const int maxn = 300, maxm = maxn * maxn;
int n, m, out[maxm | 1][5];
void addEdge(int a, int b, int c) {
	out[m][0] = 3;
	out[m][1] = a;
	out[m][2] = b;
	out[m++][3] = c;
}
void addEdge(int a, int b, int c, int d) {
	out[m][0] = 4;
	out[m][1] = a;
	out[m][2] = b;
	out[m][3] = c;
	out[m++][4] = d;
}
void showEdge() {
	printf("%d\n", m);
	for(int i = 0; i < m; ++i)
		for(int j = 0; j <= out[i][0]; ++j)
			printf("%d%c", out[i][j], " \n"[j == out[i][0]]);
}
int main() {
	scanf("%d", &n);
	if(n & 1) {
		for(int i = 3; i <= n; i += 2) {
			addEdge(1, i - 1, i);
			addEdge(1, i - 1, i);
			for(int j = 3; j < i; j += 2) {
				addEdge(j - 1, i, j, i - 1);
				addEdge(j - 1, i, j, i - 1);
			}
		}
	} else {
		addEdge(1, 2, 3, 4);
		addEdge(1, 2, 4, 3);
		addEdge(1, 3, 2, 4);
		for(int i = 6; i <= n; i += 2) {
			addEdge(1, i - 1, i);
			addEdge(2, i - 1, i);
			addEdge(1, i, 2, i - 1);
			for(int j = 4; j < i; j += 2) {
				addEdge(j - 1, i, j, i - 1);
				addEdge(j - 1, i, j, i - 1);
			}
		}
	}
	showEdge();
	return 0;
}
