#include <cstdio>
#include <algorithm>

using std::max;

#define N 100000
#define M 500000

int T, n, m, u, v, a[N + 9], f[N + 9];
int d[N + 9];

void join(int a, int b) {
	f[a] = b;
}

int find(int e) {
	return f[e] == e ? e : f[e] = find(f[e]);
}

bool pan() {
	int r = -1;
	for (int i = 1; i <= n; ++i) {
		if (r == - 1) {
			if (d[i]) r = find(i);
			continue;
		}
		if (d[i] && find(i) != r) return false;
	}
	return true;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			d[i] = 0;
			f[i] = i;
			scanf("%d", a + i);
		}
			
		while (m--) {
			scanf("%d%d", &u, &v);
			join(find(u), find(v));
			++d[u];
			++d[v];
		}
		int s = 0, c = 0, t = 0;
		for (int i = 1; i <= n; ++i) {
			if (d[i] & 1) {
				++d[i];
				++c;
			}
			if (d[i] >> 1 & 1) s ^= a[i];
		}
		if (c == 1 || c > 2 || !pan()) {
			puts("Impossible");
			continue;
		}
		if (c) {
			t = s;
		} else {
			for (int i = 1; i <= n; ++i)
				if (d[i]) t = max(t, s ^ a[i]);
		}
		printf("%d\n", t);
	}
	
	return 0;
}
