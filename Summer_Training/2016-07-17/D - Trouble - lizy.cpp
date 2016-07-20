#include <cstdio>
#include <cstring>

#define P 2000003

typedef long long i64;

int T, n;
i64 a[5][209];
i64 s[2 * P];
bool u[2 * P];

void ins(long long x) {
	int k = (x % P + P) % P;
	while (u[k]) ++k;
	u[k] = true;
	s[k] = x;
}

bool find(long long x) {
	for (int k = (x % P + P) % P; u[k]; ++k) if (s[k] == x) return true;
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < n; ++j) scanf("%I64d", a[i] + j);
		memset(u, 0, sizeof u);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				ins(a[0][i] + a[1][j]);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				for (int k = 0; k < n; ++k) {
				if (find(-(a[3][i] + a[4][j] + a[2][k]))) {
					puts("Yes");
					goto NEXT;
				}
			}
		puts("No");
		NEXT: continue;
	}
	return 0;
}
