#include <bits/stdc++.h>
using namespace std;
const int maxn = (int)1e5 + 1;
int n, m, seq[maxn];
int idx(int x, int y) {
	return x * m + y;
}
int main() {
	bool flip = 0;
	scanf("%d%d", &n, &m);
	if(n > m) {
		swap(n, m);
		flip = 1;
	} // now, n <= m
	if((n == 1 || n == 2) && (m == 2 || m == 3)) {
		puts("NO");
		return 0;
	}
	puts("YES");
	if(n == 3 && m == 3) {
		seq[0] = 5, seq[1] = 0, seq[2] = 7;
		seq[3] = 6, seq[4] = 4, seq[5] = 2;
		seq[6] = 1, seq[7] = 8, seq[8] = 3;
	} else if(n == 1) {
		int tot = 0;
		for(int i = 1; i < m; i += 2)
			seq[i] = tot++;
		for(int i = 0; i < m; i += 2)
			seq[i] = tot++;
	} else {
		for(int i = 0; i < n; ++i) {
			int adt = i & 1 ? m - 2 : 0;
			for(int j = 0; j < m; ++j) {
				seq[idx(j & 1 ? (i + 1) % n : i, j)] = idx(i, (j + adt) % m);
			}
		}
	}
	if(flip) {
		for(int j = 0; j < m; ++j)
			for(int i = 0; i < n; ++i) {
				int val = seq[idx(i, j)], x = val / m, y = val % m;
				printf("%d%c", y * n + x + 1, " \n"[i == n - 1]);
			}
	} else {
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				printf("%d%c", seq[idx(i, j)] + 1, " \n"[j == m - 1]);
	}
	return 0;
}
