#include <cstdio>
#include <cctype>
#include <algorithm>

#define N 100000

using namespace std;

int n, m, l, r;
int a[N + 9], f[19][N + 9];
int lg2[N + 9];

void get(int &x) {
	x = 0;
	int c;
	while (!isdigit(c = getchar()));
	x = c - '0';
	while (isdigit(c = getchar()))
		x = x * 10 + c - '0';
}

int que(int l, int r) {
	int j = lg2[r - l + 1];
	return min(f[j][l], f[j][r - (1 << j) + 1]);
}

int find(int ll, int rr, int k) {
	int l = ll, r = rr, m;
	while (l < r) {
		m = (l + r) >> 1;
		if (que(ll, m) <= k) r = m;
		else l = m + 1;
	}
	return a[l] <= k? l : rr + 1;
}

int main() {
	for (int i = 2; i <= N; ++i) lg2[i] = lg2[i >> 1] + 1;
	int T;
	get(T);
	while (T--) {
		get(n);
		for (int i = 1; i <= n; ++i) {
			get(a[i]);
			f[0][i] = a[i];
		}
		for (int j = 1; 1 << j <= n; ++j)
			for (int i = 1; i + (1 << j) - 1 <= n; ++i)
				f[j][i] = min(f[j - 1][i], f[j-1][i + (1 << j - 1)]);
		get(m);
		while (m--) {
			get(l), get(r);
			int v = a[l], k;
			while (l < r) {
				//printf("%d %d\n", l, v);
				k = find(l + 1, r, v);
				if (k > r) break;
				v %= a[k];
				l = k;
			}
			printf("%d\n", v);
		}
	}
}
